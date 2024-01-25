import os
import sqlite3
import MolDisplay

class Database:
    def __init__(self, reset=False):
        if (reset==True):
            if os.path.exists( 'molecules.db' ):
                os.remove( 'molecules.db' )

        self.conn = sqlite3.connect('molecules.db')

    def create_tables(self):
        self.conn.execute("""CREATE TABLE IF NOT EXISTS Elements
                           (ELEMENT_NO   INTEGER     NOT NULL,
                            ELEMENT_CODE VARCHAR(3)  NOT NULL,
                            ELEMENT_NAME VARCHAR(32) NOT NULL,
                            COLOUR1      CHAR(6)     NOT NULL,
                            COLOUR2      CHAR(6)     NOT NULL,
                            COLOUR3      CHAR(6)     NOT NULL,
                            RADIUS       DECIMAL(3)  NOT NULL,
                            PRIMARY KEY (ELEMENT_CODE));""");

        self.conn.execute("""CREATE TABLE IF NOT EXISTS Atoms
                           (ATOM_ID      INTEGER      NOT NULL,
                            ELEMENT_CODE VARCHAR(3)   NOT NULL,
                            X            DECIMAL(7,4) NOT NULL,
                            Y            DECIMAL(7,4) NOT NULL,
                            Z            DECIMAL(7,4) NOT NULL,
                            PRIMARY KEY (ATOM_ID),
                            FOREIGN KEY (ELEMENT_CODE) REFERENCES Elements);""");

        self.conn.execute("""CREATE TABLE IF NOT EXISTS Bonds
                           (BOND_ID INTEGER NOT NULL,
                            A1      INTEGER NOT NULL,
                            A2      INTEGER NOT NULL,
                            EPAIRS  INTEGER NOT NULL,
                            PRIMARY KEY (BOND_ID));""");

        self.conn.execute("""CREATE TABLE IF NOT EXISTS Molecules
                           (MOLECULE_ID INTEGER NOT NULL,
                            NAME        TEXT    NOT NULL UNIQUE,
                            PRIMARY KEY (MOLECULE_ID));""");

        self.conn.execute("""CREATE TABLE IF NOT EXISTS MoleculeAtom
                           (MOLECULE_ID INTEGER NOT NULL,
                            ATOM_ID     INTEGER NOT NULL,
                            PRIMARY KEY (MOLECULE_ID, ATOM_ID),
                            FOREIGN KEY (MOLECULE_ID) REFERENCES Molecules,
                            FOREIGN KEY (ATOM_ID)     REFERENCES Atoms);""");

        self.conn.execute("""CREATE TABLE IF NOT EXISTS MoleculeBond
                           (MOLECULE_ID INTEGER NOT NULL,
                            BOND_ID     INTEGER NOT NULL,
                            PRIMARY KEY (MOLECULE_ID, BOND_ID),
                            FOREIGN KEY (MOLECULE_ID) REFERENCES Molecules,
                            FOREIGN KEY (BOND_ID)     REFERENCES Bonds);""");
    
        self.conn.commit()

    def __setitem__(self, table, values):
        if (table=="Elements"):
            self.conn.execute("""INSERT OR IGNORE
                                 INTO Elements (ELEMENT_NO, ELEMENT_CODE, ELEMENT_NAME, COLOUR1, COLOUR2, COLOUR3, RADIUS)
                                 VALUES (?, ?, ?, ?, ?, ?, ?)""", (values))
        elif (table=="Atoms"):
            self.conn.execute("""INSERT OR IGNORE
                                 INTO Atoms (ELEMENT_CODE, X, Y, Z)
                                 VALUES (?, ?, ?, ?)""", (values))
            
        elif (table=="Bonds"):
            self.conn.execute("""INSERT OR IGNORE
                                 INTO Bonds (A1, A2, EPAIRS)
                                 VALUES (?, ?, ?)""", (values))
            
        elif (table=="Molecules"):
            self.conn.execute("""INSERT OR IGNORE
                                 INTO Molecules (NAME)
                                 VALUES (?)""", (values,))
        
        elif (table=="MoleculeAtom"):
            self.conn.execute("""INSERT OR IGNORE
                                 INTO MoleculeAtom (MOLECULE_ID, ATOM_ID)
                                 VALUES (?, ?)""", (values))
            
        elif (table=="MoleculeBond"):
            self.conn.execute("""INSERT OR IGNORE
                                 INTO MoleculeBond (MOLECULE_ID, BOND_ID)
                                 VALUES (?, ?)""", (values))
            
        self.conn.commit()

    def add_atom(self, molname, atom):
        thisatom = atom

        cursor = self.conn.cursor()

        #add to Atoms table
        cursor.execute("""INSERT OR IGNORE
                          INTO Atoms (ELEMENT_CODE, X, Y, Z)
                          VALUES (?, ?, ?, ?)""", (thisatom.atom.element, thisatom.atom.x, thisatom.atom.y, thisatom.atom.z))
        
        atomid = cursor.lastrowid
        
        #get values and add to MoleculeAtom table
        moleculenum = self.conn.execute("""SELECT Molecules.MOLECULE_ID
                                           FROM Molecules
                                           WHERE Molecules.NAME='%s'""" % molname)

        self.conn.execute("""INSERT OR IGNORE
                             INTO MoleculeAtom (MOLECULE_ID, ATOM_ID)
                             VALUES (?, ?)""", (moleculenum.fetchone()[0], atomid))

        self.conn.commit()

    def add_bond(self, molname, bond):
        thisbond = bond

        #add to Bonds table
        cursor = self.conn.cursor()
        cursor.execute("""INSERT OR IGNORE
                          INTO Bonds (A1, A2, EPAIRS)
                          VALUES (?, ?, ?)""", (thisbond.bond.a1, thisbond.bond.a2, thisbond.bond.epairs))
        
        bondid = cursor.lastrowid

        #get values and add to MoleculeBond table
        moleculenum = self.conn.execute("""SELECT Molecules.MOLECULE_ID
                                           FROM Molecules
                                           WHERE Molecules.NAME='%s'""" % molname)
        
        self.conn.execute("""INSERT OR IGNORE
                             INTO MoleculeBond (MOLECULE_ID, BOND_ID)
                             VALUES (?, ?)""", (moleculenum.fetchone()[0], bondid))
        
        self.conn.commit()

    def add_molecule(self, name, fp):
        moleculenew = MolDisplay.Molecule()
        atomIndex = 0
        bondIndex = 0

        if (moleculenew.parse(fp) == 1):
            return 1
        else:
            numrowsbefore = self.conn.execute("""SELECT COUNT(*) FROM Molecules""")

            #add to Molecules table
            self.conn.execute("""INSERT OR IGNORE
                                INTO Molecules (NAME)
                                VALUES (?)""", (name,))

            numrowsafter = self.conn.execute("""SELECT COUNT(*) FROM Molecules""")

            diff = numrowsafter.fetchone()[0] - numrowsbefore.fetchone()[0]

            if (diff==1):
                #add atoms
                for i in range(moleculenew.atom_no):
                    currAtom = MolDisplay.Atom(moleculenew.get_atom(atomIndex))
                    self.add_atom(name, currAtom)
                    atomIndex = atomIndex + 1

                #add bonds
                for i in range(moleculenew.bond_no):
                    currBond = MolDisplay.Bond(moleculenew.get_bond(bondIndex))
                    self.add_bond(name, currBond)
                    bondIndex = bondIndex + 1

            self.conn.commit()
        

    def load_mol(self, name):
        moleculenew = MolDisplay.Molecule()
        
        #get atoms
        allatoms = self.conn.execute("""SELECT Atoms.ELEMENT_CODE, Atoms.X, Atoms.Y, Atoms.Z FROM Atoms, Molecules, MoleculeAtom
                                        WHERE
                                        (Molecules.NAME='%s' AND MoleculeAtom.MOLECULE_ID=Molecules.MOLECULE_ID AND Atoms.ATOM_ID=MoleculeAtom.ATOM_ID)
                                        ORDER BY Atoms.ATOM_ID""" % name)
        
        tableatoms = allatoms.fetchall()

        #append atoms
        i=0
        for row in tableatoms:
            moleculenew.append_atom(tableatoms[i][0], tableatoms[i][1], tableatoms[i][2], tableatoms[i][3])
            i=i+1

        #get bonds
        allbonds = self.conn.execute("""SELECT Bonds.A1, Bonds.A2, Bonds.EPAIRS FROM Bonds, Molecules, MoleculeBond
                                        WHERE
                                        (Molecules.NAME='%s' AND MoleculeBond.MOLECULE_ID=Molecules.MOLECULE_ID AND Bonds.BOND_ID=MoleculeBond.BOND_ID)
                                        ORDER BY Bonds.BOND_ID""" % name)

        tablebonds = allbonds.fetchall()

        #append bonds
        i=0
        for row in tablebonds:
            moleculenew.append_bond(tablebonds[i][0], tablebonds[i][1], tablebonds[i][2])
            i=i+1
        
        return moleculenew

    def radius(self):
        #get values
        values = self.conn.execute("""SELECT Elements.ELEMENT_CODE, Elements.RADIUS FROM Elements""")

        table = values.fetchall()

        #create dictionary
        dictionary_radius = {}
        i=0
        for row in table:
            dictionary_radius[table[i][0]] = table[i][1]
            i=i+1

        return dictionary_radius

    def element_name(self):
        #get values
        values = self.conn.execute("""SELECT Elements.ELEMENT_CODE, Elements.ELEMENT_NAME FROM Elements""")
        table = values.fetchall()

        #create dictionary
        dictionary_name = {}
        i=0
        for row in table:
            dictionary_name[table[i][0]] = table[i][1]
            i=i+1

        return dictionary_name

    def radial_gradients(self):
        #get values
        values = self.conn.execute("""SELECT Elements.ELEMENT_NAME, Elements.COLOUR1, Elements.COLOUR2, Elements.COLOUR3 FROM Elements""")
        table = values.fetchall()

        #create dictionary
        radialGradientSVG = "\n"
        i=0
        for row in table:
            radialGradientSVG += """<radialGradient id="%s" cx="-50%%" cy="-50%%" r="220%%" fx="20%%" fy="20%%">\n""" % (table[i][0])
            radialGradientSVG += """<stop offset="0%%" stop-color="#%s"/>\n""" % (table[i][1])
            radialGradientSVG += """<stop offset="50%%" stop-color="#%s"/>\n""" % (table[i][2])
            radialGradientSVG += """<stop offset="100%%" stop-color="#%s"/>\n""" % (table[i][3])
            radialGradientSVG += """</radialGradient>\n"""
            
            i=i+1

        return radialGradientSVG