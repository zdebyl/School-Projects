import sys
import MolDisplay
import molsql
from urllib import parse
import cgi
import os
from http.server import HTTPServer, BaseHTTPRequestHandler;

db = molsql.Database(reset=True)

class MyHandler( BaseHTTPRequestHandler ):
   def do_GET(self):
      if self.path == "/":
         file = open("home.html", "r")

         htmlstring = file.read()

         self.send_response( 200 );
         self.send_header( "Content-type", "text/html" );
         self.send_header( "Content-length", len(htmlstring) );
         self.end_headers();

         db.create_tables();
         db['Elements'] = (0, 'def', 'default', 'FFFFFF', '050505', '020202', 25)

         self.wfile.write( bytes( htmlstring, "utf-8" ) );
      
         db.conn.commit()

      elif self.path == "/script.js":
         file = open("script.js", "r")

         jsString = file.read()

         self.send_response(200)
         self.send_header("Content-type", "text/javascript")
         self.send_header("Content-length", len(jsString))
         self.end_headers();

         self.wfile.write( bytes( jsString, "utf-8" ) );
      
      elif self.path == "/style.css":
         file = open("style.css", "r")

         cssString = file.read()

         self.send_response(200)
         self.send_header("Content-type", "text/css")
         self.send_header("Content-length", len(cssString))
         self.end_headers();

         self.wfile.write( bytes( cssString, "utf-8" ) );

      elif self.path == "/viewmolecules":
         molecule = MolDisplay.Molecule()

         #get molecule names
         allvalues = db.conn.execute("""SELECT Molecules.NAME FROM Molecules""")
         moleculestodisplay = allvalues.fetchall()

         #print molecule names
         i=0
         string = ""
         for value in moleculestodisplay:
            molecule = db.load_mol(moleculestodisplay[i][0])
            string += moleculestodisplay[i][0]
            string += ": number of atoms = " + str(molecule.atom_no)
            string += ", number of bonds = " + str(molecule.bond_no)
            string += "\n"
            i=i+1
         
         self.send_response( 200 )
         self.send_header( "Content-type", "text/html" )
         self.send_header( "Content-length", len(string) )
         self.end_headers()

         self.wfile.write( bytes(string, "utf-8" ) )

      else:
         self.send_response( 404 );
         self.end_headers();
         self.wfile.write( bytes( "404: not found", "utf-8" ) );

   def do_POST(self):
      if self.path == "/molecule":
         molecule = MolDisplay.Molecule()

         self.send_response( 200 )
         self.send_header( "Content-type", "text/html" )
         self.send_header( "Content-length", self.headers.get('content-length') )
         self.end_headers()

         field = cgi.FieldStorage(
            fp = self.rfile,
            headers = self.headers,
            environ = {'REQUEST_METHOD': 'POST', 'CONTENT_TYPE': self.headers['Content-Type']}
         )

         moleculename = field.getvalue("name")
         file = field["filename"].file.read()

         if not moleculename:
            self.wfile.write( bytes("No molecule name enterred, file not uploaded.", "utf-8" ) )
         elif len(moleculename) > 2147483647:
            self.wfile.write( bytes("Error in molecule name, file not uploaded.", "utf-8" ) )
         else:
            #check if name exists
            elementvalue = db.conn.execute("""SELECT Molecules.NAME FROM Molecules WHERE (Molecules.NAME='%s')""" % moleculename)
                  
            if elementvalue.fetchone() is not None:
               self.wfile.write( bytes("This molecule name is already used, please use a different one.", "utf-8" ) )
            else:
               tempfile = open("file.sdf", "w+")
               tempfile.write(file.decode())
               tempfile.seek(0)

               if (db.add_molecule(moleculename, tempfile)==1):
                  self.wfile.write( bytes("Error in file, file not uploaded.", "utf-8" ) )
               else:
                  self.wfile.write( bytes("file uploaded successfully!", "utf-8" ) )

               tempfile.close()
               os.remove("file.sdf")
               db.conn.commit()
            
      elif self.path == "/addelement":
         self.send_response( 200 );
         self.send_header( "Content-type", "text/html" );
         self.send_header( "Content-length", self.headers.get('content-length') );
         self.end_headers();

         length = int(self.headers.get('content-length'))
         field_data = self.rfile.read(length)
         fields = parse.parse_qs(str(field_data,"utf-8"))
         
         error = 0

         #check that all entries have been entered
         if len(fields) != 7:
            error = 1
         else:
            #get all values entered
            number = fields["elementnumber"][0]
            code = fields["elementcode"][0]
            name = fields["elementname"][0]
            colour1 = fields["elementcolour1"][0]
            colour2 = fields["elementcolour2"][0]
            colour3 = fields["elementcolour3"][0]
            radius = fields["elementradius"][0]

            #check for malicious entries
            if not number.isdigit():
               error = 2
            elif len(code)>3 or not code.isalpha():
               error = 2
            elif len(name)>32 or not name.isalpha():
               error = 2
            elif len(colour1)!=6 or not colour1.isalnum():
               error = 2
            elif len(colour2)!=6 or not colour2.isalnum():
               error = 2
            elif len(colour3)!=6 or not colour3.isalnum():
               error = 2
            elif len(radius)>4 or not radius.replace(".","").isdigit():
               error = 2
            else:
               #check if entry is already in database and remove it if it is
               elementvalue = db.conn.execute("""SELECT Elements.ELEMENT_NO FROM Elements WHERE (Elements.ELEMENT_NO='%s')""" % number)
               
               if elementvalue.fetchone() is not None:
                  db.conn.execute("""DELETE FROM Elements WHERE (Elements.ELEMENT_NO='%s')""" % number)
       
         #output
         if error == 0:
            db['Elements'] = (number, code, name, colour1, colour2, colour3, radius)
            self.wfile.write( bytes("element added!", "utf-8" ) )
         elif error == 1:
            self.wfile.write( bytes("not all entries filled in, element not added.", "utf-8" ) )
         elif error == 2:
            self.wfile.write( bytes("error in entries, element not added.", "utf-8" ) )
         
         db.conn.commit()

      elif self.path == "/removeelement":
         self.send_response( 200 );
         self.send_header( "Content-type", "text/html" );
         self.send_header( "Content-length", self.headers.get('content-length') );
         self.end_headers();

         length = int(self.headers.get('content-length'))
         field_data = self.rfile.read(length)
         fields = parse.parse_qs(str(field_data,"utf-8"))
         
         error = 0

         #check that all entries have been entered
         if len(fields) != 1:
            error = 1
         else:
            #get all values entered
            name = fields["removeelementname"][0]

            #check for malicious entries
            if len(name)>32 or not name.isalpha():
               error = 2
            else:
               #check if entry is already in database and remove it if it is
               elementvalue = db.conn.execute("""SELECT Elements.ELEMENT_NAME FROM Elements WHERE (Elements.ELEMENT_NAME='%s')""" % name)
               
               if elementvalue.fetchone() is not None:
                  db.conn.execute("""DELETE FROM Elements WHERE (Elements.ELEMENT_NAME='%s')""" % name)

               else:
                  error = 3

         #output
         if error == 0:
            self.wfile.write( bytes("element removed!", "utf-8" ) )
         elif error == 1:
            self.wfile.write( bytes("entry not filled in, element not removed.", "utf-8" ) )
         elif error == 2:
            self.wfile.write( bytes("error in entry, element not removed.", "utf-8" ) )
         elif error == 3:
            self.wfile.write( bytes("entry not in table, element not removed.", "utf-8" ) )

         db.conn.commit()

      elif self.path == "/displaymolecule":
         molecule = MolDisplay.Molecule()

         length = int(self.headers.get('content-length'))
         field_data = self.rfile.read(length)
         fields = parse.parse_qs(str(field_data,"utf-8"))

         #check if value was entered
         if len(fields) != 1:
            self.send_response( 200 );
            self.send_header( "Content-type", "text/html" );
            self.send_header( "Content-length", self.headers.get('content-length') );
            self.end_headers();

            self.wfile.write( bytes("No value entered, molecule not displayed.", "utf-8" ) );

         else:
            name = fields["displaymolecule"][0]

            #check if entry is in database
            moleculevalue = db.conn.execute("""SELECT Molecules.NAME FROM Molecules WHERE (Molecules.NAME='%s')""" % name)
            
            if moleculevalue.fetchone() is None:
               self.send_response( 200 );
               self.send_header( "Content-type", "text/html" );
               self.send_header( "Content-length", self.headers.get('content-length') );
               self.end_headers();

               self.wfile.write( bytes("No molecule with this name, molecule not displayed.", "utf-8" ) ) 
            else:
               molecule = db.load_mol(name)
               
               message = "Enter a degree to rotate the molecule!"
         
               molecule.sort()
               oldheader = MolDisplay.header
               MolDisplay.header += db.radial_gradients()
               moleculesvg = molecule.svg()

               htmlString = """
                        <div>
                           {}
                        </div>
                        <div>
                           <label>X-degrees:</label>
                           <input type="text" name="xdegree" id="x" />
                           <button id="rotation-buttonx">Rotate X</button><br>
                           <label>Y-degrees:</label>
                           <input type="text" name="ydegree" id="y" />
                           <button id="rotation-buttony">Rotate Y</button><br>
                           <label>Z-degrees:</label>
                           <input type="text" name="zdegree" id="z" />
                           <button id="rotation-buttonz">Rotate Z</button>
                           <p>{}</p>

                           <input type="hidden" id="moleculename" value="{}">
                        </div>
                        """.format(moleculesvg, message, name)

               self.send_response( 200 );
               self.send_header( "Content-type", "text/html" );
               self.send_header( "Content-length", len(htmlString) );
               self.end_headers();

               self.wfile.write( bytes(htmlString, "utf-8" ) );

               MolDisplay.header = oldheader

      elif self.path == "/rotation":
         molecule = MolDisplay.Molecule()

         length = int(self.headers.get('content-length'))
         field_data = self.rfile.read(length)
         fields = parse.parse_qs(str(field_data,"utf-8"))

         message = "Enter a degree to rotate the molecule!"

         error = 0

         #check if value is entered
         if (len(fields)!=3):
            message = "Must enter a value to rotate, please try again."
            error = 1
         else:
            degree = fields["degree"][0]

         #get values
         type = str(fields["typerequest"][0])
         name = fields["moleculename"][0]

         #check value entered
         if (len(fields)==3) and not degree.isdigit():
            message = "Invalid entry (must be an integer value), please try again."
            error = 1

         #get molecule how it previously was
         molecule = db.load_mol(name)

         if error == 0:
            degree = int(degree)

            #rotate
            if (type=="xrotation"):
               molecule.rotation(degree, 0, 0)
            if (type=="yrotation"):
               molecule.rotation(0, degree, 0)
            if (type=="zrotation"):
               molecule.rotation(0, 0, degree)

            #update molecule in database
            allatoms = db.conn.execute("""SELECT Atoms.ATOM_ID FROM Atoms, Molecules, MoleculeAtom
                                          WHERE
                                          (Molecules.NAME='%s' AND MoleculeAtom.MOLECULE_ID=Molecules.MOLECULE_ID AND Atoms.ATOM_ID=MoleculeAtom.ATOM_ID)
                                          ORDER BY Atoms.ATOM_ID""" % name)
            
            tableatoms = allatoms.fetchall()

            j=0
            for i in tableatoms:
               thisatom = MolDisplay.Atom(molecule.get_atom(j))
               newx = thisatom.atom.x
               newy = thisatom.atom.y
               newz = thisatom.atom.z
               atomid = int(tableatoms[j][0])

               db.conn.execute("""UPDATE Atoms SET X=?, Y=?, Z=? WHERE ATOM_ID=?""", (newx, newy, newz, atomid))

               j=j+1
         
         molecule.sort()
         oldheader = MolDisplay.header
         MolDisplay.header += db.radial_gradients()
         moleculesvg = molecule.svg()

         htmlString = """
                        <div>
                           {}
                        </div>
                        <div>
                           <label>X-degrees:</label>
                           <input type="text" name="xdegree" id="x" />
                           <button id="rotation-buttonx">Rotate X</button><br>
                           <label>Y-degrees:</label>
                           <input type="text" name="ydegree" id="y" />
                           <button id="rotation-buttony">Rotate Y</button><br>
                           <label>Z-degrees:</label>
                           <input type="text" name="zdegree" id="z" />
                           <button id="rotation-buttonz">Rotate Z</button>
                           <p>{}</p>

                           <input type="hidden" id="moleculename" value="{}">
                        </div>
                        """.format(moleculesvg, message, name)
         
         self.send_response( 200 );
         self.send_header( "Content-type", "text/html" );
         self.send_header( "Content-length", len(htmlString) );
         self.end_headers();

         self.wfile.write( bytes(htmlString, "utf-8" ) );

         MolDisplay.header = oldheader

      else:
         self.send_response( 404 )
         self.end_headers()
         self.wfile.write( bytes( "404: not found", "utf-8" ) )

httpd = HTTPServer( ( 'localhost', int(sys.argv[1]) ), MyHandler )
httpd.serve_forever()