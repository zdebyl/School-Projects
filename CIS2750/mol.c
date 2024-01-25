#include "mol.h"

void atomset( atom *atom, char element[3], double *x, double *y, double *z ) {
    strcpy(atom->element, element);
    atom->x = *x;
    atom->y = *y;
    atom->z = *z;
}

void atomget( atom *atom, char element[3], double *x, double *y, double *z ) {
    strcpy(element, atom->element);
    *x = atom->x;
    *y = atom->y;
    *z = atom->z;
}

void bondset( bond *bond, unsigned short *a1, unsigned short *a2, atom **atoms, unsigned char *epairs ) {
    bond->a1 = *a1;
    bond->a2 = *a2;
    bond->atoms = *atoms;
    bond->epairs = *epairs;
    compute_coords(bond);
}

void bondget( bond *bond, unsigned short *a1, unsigned short *a2, atom **atoms, unsigned char *epairs ) {
    *a1 = bond->a1;
    *a2 = bond->a2;
    *atoms = bond->atoms;
    *epairs = bond->epairs;
}

void compute_coords( bond *bond ) {
    bond->x1 = bond->atoms[bond->a1].x;
    bond->x2 = bond->atoms[bond->a2].x;
    bond->y1 = bond->atoms[bond->a1].y;
    bond->y2 = bond->atoms[bond->a2].y;
    bond->z = (bond->atoms[bond->a1].z + bond->atoms[bond->a2].z)/2;
    bond->len = sqrt((bond->y2-bond->y1)*(bond->y2-bond->y1) + (bond->x2-bond->x1)*(bond->x2-bond->x1));
    bond->dx = (bond->x2 - bond->x1) / bond->len;
    bond->dy = (bond->y2 - bond->y1) / bond->len;
}

molecule *molmalloc( unsigned short atom_max, unsigned short bond_max ) {
    molecule *newMolecule;

    //allocate memory
    newMolecule = malloc(sizeof(struct molecule));

    if (newMolecule==NULL) {
        return NULL;
    }

    newMolecule->atoms = malloc(sizeof(struct atom)*atom_max);

    if (newMolecule->atoms==NULL) {
        return NULL;
    }

    newMolecule->atom_ptrs = malloc(sizeof(struct atom*)*atom_max);

    if (newMolecule->atom_ptrs==NULL) {
        return NULL;
    }

    newMolecule->bonds = malloc(sizeof(struct bond)*bond_max);

    if (newMolecule->bonds==NULL) {
        return NULL;
    }

    newMolecule->bond_ptrs = malloc(sizeof(struct bond*)*bond_max);

    if (newMolecule->bond_ptrs==NULL) {
        return NULL;
    }

    //assign atom and bonds number and max
    newMolecule->atom_max = atom_max;
    newMolecule->atom_no = 0;
    newMolecule->bond_max = bond_max;
    newMolecule->bond_no = 0;

    return newMolecule;
}

molecule *molcopy( molecule *src ) {
    molecule *newMolecule;
    
    //allocate memory
    newMolecule = molmalloc(src->atom_max, src->bond_max);

    //add atoms and bonds
    for (int i=0; i<src->atom_no; i++) {
        molappend_atom(newMolecule, src->atoms+i);
    }

    for (int i=0; i<src->bond_no; i++) {
        molappend_bond(newMolecule, src->bonds+i);
    }

    //assign atom and bond number
    newMolecule->atom_no = src->atom_no;
    newMolecule->bond_no = src->bond_no;

    return newMolecule;
}

void molfree( molecule *ptr ) {
    free(ptr->bond_ptrs);
    free(ptr->bonds);
    free(ptr->atom_ptrs);
    free(ptr->atoms);
    free(ptr);
}

void molappend_atom( molecule *molecule, atom *atom ) {
    int newAtomPosition;

    //if number of atoms is surpassing max number of atoms
    if (molecule->atom_max==molecule->atom_no) {
        if (molecule->atom_max==0) {
            molecule->atom_max=1;
            molecule->atoms = realloc(molecule->atoms,sizeof(struct atom)*molecule->atom_max);
            molecule->atom_ptrs = realloc(molecule->atom_ptrs,sizeof(struct atom*)*molecule->atom_max);
        } else {
            molecule->atom_max=molecule->atom_max*2;
            molecule->atoms = realloc(molecule->atoms,sizeof(struct atom)*molecule->atom_max);
            molecule->atom_ptrs = realloc(molecule->atom_ptrs,sizeof(struct atom*)*molecule->atom_max);
        }

        for (int i=0; i<molecule->atom_no; i++) {
            *(molecule->atom_ptrs+i) = molecule->atoms+i;
        }
    }

    //increment atom number
    molecule->atom_no++;

    //add new atom
    newAtomPosition=molecule->atom_no-1;

    *(molecule->atoms+newAtomPosition) = *atom;
    *(molecule->atom_ptrs+newAtomPosition) = molecule->atoms+newAtomPosition;
}

void molappend_bond( molecule *molecule, bond *bond ) {
    int newBondPosition;

    //if number of bonds is surpassing max number of bonds
    if (molecule->bond_max==molecule->bond_no) {
        if (molecule->bond_max==0) {
            molecule->bond_max=1;
            molecule->bonds = realloc(molecule->bonds,sizeof(struct bond)*molecule->bond_max);
            molecule->bond_ptrs = realloc(molecule->bond_ptrs,sizeof(struct bond*)*molecule->bond_max);
        } else {
            molecule->bond_max=molecule->bond_max*2;
            molecule->bonds = realloc(molecule->bonds,sizeof(struct bond)*molecule->bond_max);
            molecule->bond_ptrs = realloc(molecule->bond_ptrs,sizeof(struct bond*)*molecule->bond_max);
        }

        for (int i=0; i<molecule->bond_no; i++) {
            *(molecule->bond_ptrs+i) = molecule->bonds+i;
        }
    }

    //increment bond number
    molecule->bond_no++;

    //add new bond
    newBondPosition=molecule->bond_no-1;

    *(molecule->bonds+newBondPosition) = *bond;
    *(molecule->bond_ptrs+newBondPosition) = molecule->bonds+newBondPosition;
}

void molsort( molecule *molecule ) {
    qsort(molecule->atom_ptrs, molecule->atom_no, sizeof(atom*), atom_cmp);
    qsort(molecule->bond_ptrs, molecule->bond_no, sizeof(bond*), bond_cmp);
}

void xrotation( xform_matrix xform_matrix, unsigned short deg ) {
    double radians;

    //convert to radians
    radians = deg * (M_PI/180);

    //create matrix
    xform_matrix[0][0] = 1;
    xform_matrix[0][1] = 0;
    xform_matrix[0][2] = 0;

    xform_matrix[1][0] = 0;
    xform_matrix[1][1] = cos(radians);
    xform_matrix[1][2] = -sin(radians);

    xform_matrix[2][0] = 0;
    xform_matrix[2][1] = sin(radians);
    xform_matrix[2][2] = cos(radians);
}

void yrotation( xform_matrix xform_matrix, unsigned short deg ) {
    double radians;

    //convert to radians
    radians = deg * (M_PI/180);

    //create matrix
    xform_matrix[0][0] = cos(radians);
    xform_matrix[0][1] = 0;
    xform_matrix[0][2] = sin(radians);

    xform_matrix[1][0] = 0;
    xform_matrix[1][1] = 1;
    xform_matrix[1][2] = 0;

    xform_matrix[2][0] = -sin(radians);
    xform_matrix[2][1] = 0;
    xform_matrix[2][2] = cos(radians);
}

void zrotation( xform_matrix xform_matrix, unsigned short deg ) {
    double radians;

    //convert to radians
    radians = deg * (M_PI/180);

    //create matrix
    xform_matrix[0][0] = cos(radians);
    xform_matrix[0][1] = -sin(radians);
    xform_matrix[0][2] = 0;

    xform_matrix[1][0] = sin(radians);
    xform_matrix[1][1] = cos(radians);
    xform_matrix[1][2] = 0;

    xform_matrix[2][0] = 0;
    xform_matrix[2][1] = 0;
    xform_matrix[2][2] = 1;
}

void mol_xform( molecule *molecule, xform_matrix matrix ) {
    double newx, newy, newz;
    double x,y,z;

    //create new x,y,z values for molecule
    for (int i=0; i<molecule->atom_no; i++) {
        x = (molecule->atoms+i)->x;
        y = (molecule->atoms+i)->y;
        z = (molecule->atoms+i)->z;

        newx = matrix[0][0]*x + matrix[0][1]*y + matrix[0][2]*z;
        newy = matrix[1][0]*x + matrix[1][1]*y + matrix[1][2]*z;
        newz = matrix[2][0]*x + matrix[2][1]*y + matrix[2][2]*z;

        (molecule->atoms+i)->x = newx;
        (molecule->atoms+i)->y = newy;
        (molecule->atoms+i)->z = newz;
    }

    //update bonds
    for (int i=0; i<molecule->bond_no; i++) {
        compute_coords((molecule->bonds+i));
    }
}

int atom_cmp( const void *a, const void *b )
{
    atom **a_ptr, **b_ptr;
    double a_zvalue, b_zvalue, diff;

    //get values to compare
    a_ptr = (atom **)a;
    b_ptr = (atom **)b;

    a_zvalue = (*a_ptr)->z;
    b_zvalue = (*b_ptr)->z;

    //compare values
    diff = a_zvalue-b_zvalue;

    if (diff>0) {
        return 1;
    } else if (diff<0) {
        return -1;
    } else {
        return 0;
    }
}

int bond_cmp( const void *a, const void *b )
{
    bond **a_ptr, **b_ptr;
    double a_zvalue, b_zvalue, diff;

    //get values to compare
    a_ptr = (bond **)a;
    b_ptr = (bond **)b;

    a_zvalue = (*a_ptr)->z;
    b_zvalue = (*b_ptr)->z;

    //compare values
    diff = a_zvalue-b_zvalue;

    if (diff>0) {
        return 1;
    } else if (diff<0) {
        return -1;
    } else {
        return 0;
    }
}
