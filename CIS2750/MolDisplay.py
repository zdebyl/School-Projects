import molecule
import molsql

header = """<svg version="1.1" width="1000" height="1000"
   xmlns="http://www.w3.org/2000/svg">""";

footer = """</svg>""";
offsetx = 500;
offsety = 500;

class Atom:
   def __init__(self, c_atom):
      self.atom = c_atom
      self.z = c_atom.z

   def __str__( self ):
      return '''element: %s x: %lf y: %lf z: %lf''' % (self.atom.element, self.atom.x, self.atom.y, self.atom.z)

   def svg(self):
      xcentre = self.atom.x * 100 + offsetx
      ycentre = self.atom.y * 100 + offsety

      db = molsql.Database(reset=False)

      if db.radius().get(self.atom.element) is not None:
         rad = db.radius()[self.atom.element]
      else:
         rad = 25

      if db.element_name().get(self.atom.element) is not None:
         colour = db.element_name()[self.atom.element]
      else:
         colour = "default"
      
      return '''<circle cx="%.2f" cy="%.2f" r="%d" fill="url(#%s)"/>\n''' % (xcentre, ycentre, rad, colour)

class Bond:
   def __init__(self, c_bond):
      self.bond = c_bond
      self.z = c_bond.z

   def __str__(self):
      return '''epairs: %d a1: %d a2: %d''' % (self.bond.epairs, self.bond.a1, self.bond.a2)

   def svg(self):
      xcentre1=self.bond.x1 * 100 + offsetx
      ycentre1=self.bond.y1 * 100 + offsety
      xcentre2=self.bond.x2 * 100 + offsetx
      ycentre2=self.bond.y2 * 100 + offsety

      x1=xcentre1 - (self.bond.dy*10)
      y1=ycentre1 + (self.bond.dx*10)
      x2=xcentre2 + (self.bond.dy*10)
      y2=ycentre2 - (self.bond.dx*10)
      x3=xcentre1 + (self.bond.dy*10)
      y3=ycentre1 - (self.bond.dx*10)
      x4=xcentre2 - (self.bond.dy*10)
      y4=ycentre2 + (self.bond.dx*10)

      return '''<polygon points="%.2f,%.2f %.2f,%.2f %.2f,%.2f %.2f,%.2f" fill="green"/>\n''' % (x1,y1,x4,y4,x2,y2,x3,y3)

class Molecule(molecule.molecule):
   def __str__(self):
      toreturn = ""

      for i in range(self.atom_no):
         toreturn += Atom(self.get_atom(i)).__str__()
         toreturn += "\n"

      for i in range(self.bond_no):
        toreturn += Bond(self.get_bond(i)).__str__()
        toreturn += "\n"

      return toreturn

   def svg(self):
      toreturn = ""
      toreturn += header

      atomIndex=0
      bondIndex=0

      #sort atoms and bonds
      while (atomIndex<self.atom_no and bondIndex<self.bond_no):
         newAtom = Atom(self.get_atom(atomIndex))
         newBond = Bond(self.get_bond(bondIndex))

         if (newAtom.z<newBond.z):
            toreturn += newAtom.svg()
            atomIndex = atomIndex + 1
         else:
            toreturn += newBond.svg()
            bondIndex = bondIndex + 1

      #add rest of atoms/bonds
      if (atomIndex<self.atom_no):
         while (atomIndex<self.atom_no):
            newAtom = Atom(self.get_atom(atomIndex))
            toreturn += newAtom.svg()
            atomIndex = atomIndex + 1
      elif (bondIndex<self.bond_no):
         while (bondIndex<self.bond_no):
            newBond = Bond(self.get_bond(bondIndex))
            toreturn += newBond.svg()
            bondIndex = bondIndex + 1

      toreturn += footer

      return toreturn

   def parse(self, file):
      try:
         for i in range(3):
            file.readline()

         numAtoms = int(file.read(3))
         numBonds = int(file.read(3))

         file.readline()

         #read atoms
         for i in range(numAtoms):
            line = file.readline().split()   

            if(isinstance(line[3],bytes)==False):      
               self.append_atom(str(line[3]), float(line[0]), float(line[1]), float(line[2]))
            else:
               self.append_atom(str(line[3].decode()), float(line[0].decode()), float(line[1].decode()), float(line[2].decode()))

         #read bonds
         for i in range(numBonds):
            line = file.readline().split()
            self.append_bond(int(line[0])-1,int(line[1])-1,int(line[2]))
      except Exception:
         return 1
   
   def rotation(self, xdegree, ydegree, zdegree): 
      mx = molecule.mx_wrapper(xdegree,ydegree,zdegree)
      
      self.xform(mx.xform_matrix)

      
       
      