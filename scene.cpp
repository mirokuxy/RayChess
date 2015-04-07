//
// this provide functions to set up the scene
//

// GLM lib for matrix calculation
#include "include/glm/glm.hpp"
#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/type_ptr.hpp"

#include "object.h"
#include <cstdio>

// light 1 position and color
extern glm::vec3 light1;
extern glm::vec3 light1_ambient;
extern glm::vec3 light1_diffuse;
extern glm::vec3 light1_specular;

// global ambient term
extern glm::vec3 global_ambient;

extern Object *scene;

extern glm::vec3 background_clr;
extern float decay_a;
extern float decay_b;
extern float decay_c;

extern int objectCount;

//////////////////////////////////////////////////////////////////////////

/*******************************************
 * set up the default scene 
 *******************************************/
void set_up_default_scene() {
    // set background color
    background_clr =  glm::vec3(0.5,0.05,0.8);

    // setup global ambient term
    global_ambient = glm::vec3(0.2,0.2,0.2);

    // setup light 1
    light1 = glm::vec3(-2.0,5.0,1.0);
    light1_ambient = glm::vec3(0.1,0.1,0.1);
    light1_diffuse = glm::vec3(1.0,1.0,1.0);
    light1_specular = glm::vec3(1.0,1.0,1.0);

    // set up decay parameters
    decay_a = 0.5;
    decay_b = 0.3;
    decay_c = 0.0;

    // sphere 1
    glm::vec3 sphere1_ambient = glm::vec3(0.7, 0.7, 0.7);
    glm::vec3 sphere1_diffuse = glm::vec3(0.1, 0.5, 0.8);
    glm::vec3 sphere1_specular = glm::vec3(1.0, 1.0, 1.0);
    float sphere1_shineness = 10;
    float sphere1_reflectance = 0.4;

    glm::vec3 sphere1_ctr = glm::vec3(1.5, -0.2, -3.2);
    float sphere1_rad = 1.23;

    addSphere(++objectCount,sphere1_ambient, sphere1_diffuse, sphere1_specular, sphere1_shineness,
        sphere1_reflectance,sphere1_ctr, sphere1_rad);

    // sphere 2
    glm::vec3 sphere2_ambient = glm::vec3(0.6, 0.6, 0.6);
    glm::vec3 sphere2_diffuse = glm::vec3(1.0, 0.0, 0.25);
    glm::vec3 sphere2_specular = glm::vec3(1.0, 1.0, 1.0);
    float sphere2_shineness = 6;
    float sphere2_reflectance = 0.3;

    glm::vec3 sphere2_ctr = glm::vec3(-1.5, 0.0, -3.5);
    float sphere2_rad = 1.5;

    addSphere(++objectCount, sphere2_ambient, sphere2_diffuse, sphere2_specular, sphere2_shineness,
        sphere2_reflectance, sphere2_ctr, sphere2_rad);

    // sphere 3
    glm::vec3 sphere3_ambient = glm::vec3(0.2, 0.2, 0.2);
    glm::vec3 sphere3_diffuse = glm::vec3(0.0, 1.0, 0.25);
    glm::vec3 sphere3_specular = glm::vec3(0.0, 1.0, 0.0);
    float sphere3_shineness = 30;
    float sphere3_reflectance = 0.3;

    glm::vec3 sphere3_ctr = glm::vec3(-0.35, 1.75, -2.25);
    float sphere3_rad = 0.5;

    addSphere(++objectCount, sphere3_ambient, sphere3_diffuse, sphere3_specular, sphere3_shineness,
        sphere3_reflectance, sphere3_ctr, sphere3_rad);
}

/***************************************
 * You can create your own scene here
 ***************************************/
void set_up_user_scene() {
   // set background color
    background_clr =  glm::vec3(0.5,0.05,0.8);

    // setup global ambient term
    global_ambient = glm::vec3(0.2,0.2,0.2);

    // setup light 1
    light1 = glm::vec3(-2.0,5.0,1.0);
    light1_ambient = glm::vec3(0.1,0.1,0.1);
    light1_diffuse = glm::vec3(1.0,1.0,1.0);
    light1_specular = glm::vec3(1.0,1.0,1.0);

    // set up decay parameters
    decay_a = 0.5;
    decay_b = 0.3;
    decay_c = 0.0;

    // sphere 1
    glm::vec3 sphere1_ambient = glm::vec3(0.7, 0.7, 0.7);
    glm::vec3 sphere1_diffuse = glm::vec3(0.1, 0.5, 0.8);
    glm::vec3 sphere1_specular = glm::vec3(1.0, 1.0, 1.0);
    float sphere1_shineness = 10;
    float sphere1_reflectance = 0.4;

    glm::vec3 sphere1_ctr = glm::vec3(1.5, -0.2, -3.2);
    float sphere1_rad = 1.23;

    bool sphere1_refract = true;
    float sphere1_refractivity = 1.5;
    float sphere1_refractance = 1.0;

    addSphere(++objectCount,sphere1_ambient, sphere1_diffuse, sphere1_specular, sphere1_shineness,
        sphere1_reflectance,sphere1_ctr, sphere1_rad, sphere1_refract, sphere1_refractivity, sphere1_refractance);

    // sphere 2
    glm::vec3 sphere2_ambient = glm::vec3(0.6, 0.6, 0.6);
    glm::vec3 sphere2_diffuse = glm::vec3(1.0, 0.0, 0.25);
    glm::vec3 sphere2_specular = glm::vec3(1.0, 1.0, 1.0);
    float sphere2_shineness = 6;
    float sphere2_reflectance = 0.3;

    glm::vec3 sphere2_ctr = glm::vec3(-1.5, 0.0, -3.5);
    float sphere2_rad = 1.5;

    bool sphere2_refract = true;
    float sphere2_refractivity = 2;
    float sphere2_refractance = 1.0;

    addSphere(++objectCount, sphere2_ambient, sphere2_diffuse, sphere2_specular, sphere2_shineness,
        sphere2_reflectance, sphere2_ctr, sphere2_rad, sphere2_refract, sphere2_refractivity, sphere2_refractance);

    // sphere 3
    glm::vec3 sphere3_ambient = glm::vec3(0.2, 0.2, 0.2);
    glm::vec3 sphere3_diffuse = glm::vec3(0.0, 1.0, 0.25);
    glm::vec3 sphere3_specular = glm::vec3(0.0, 1.0, 0.0);
    float sphere3_shineness = 30;
    float sphere3_reflectance = 0.3;

    glm::vec3 sphere3_ctr = glm::vec3(-0.35, 1.75, -2.25);
    float sphere3_rad = 0.5;

    bool sphere3_refract = true;
    float sphere3_refractivity = 1.5;
    float sphere3_refractance = 0.5;

    addSphere(++objectCount, sphere3_ambient, sphere3_diffuse, sphere3_specular, sphere3_shineness,
        sphere3_reflectance, sphere3_ctr, sphere3_rad, sphere3_refract, sphere3_refractivity, sphere3_refractance);
}


// ----------------------------------------
void set_up_global_variable(){
    // set background color
    background_clr =  glm::vec3(0.5,0.05,0.8);

    // setup global ambient term
    global_ambient = glm::vec3(0.2,0.2,0.2);

    // setup light 1
    light1 = glm::vec3(-2.0,5.0,1.0);
    light1_ambient = glm::vec3(0.1,0.1,0.1);
    light1_diffuse = glm::vec3(1.0,1.0,1.0);
    light1_specular = glm::vec3(1.0,1.0,1.0);

    // set up decay parameters
    decay_a = 0.5;
    decay_b = 0.3;
    decay_c = 0.0;
}

/*******************************************
 * set up the chessboard 
 *******************************************/
void set_up_chessboard(){

    glm::vec3 mat_ambient = glm::vec3(0.1, 0.1, 0.1);
    glm::vec3 mat_diffuse = glm::vec3(0,0,0);
    glm::vec3 mat_specular = glm::vec3(1.0, 1.0, 1.0);
    float  mat_shineness = 40;

    float reflectance = 1.0;

    glm::vec3 center = glm::vec3(0.0, -0.5, -3.5);
    glm::vec3 normal = glm::vec3(0,1,0);
    glm::vec3 Xaxis = glm::vec3(1,0,0);

    int Xlen = 8;
    int Ylen = 8;

    addPlane(++objectCount,mat_ambient, mat_diffuse, mat_specular, mat_shineness, reflectance, 
        center,normal,Xaxis,Xlen,Ylen);
}

void set_up_triangles(){

    int index = 5;
    glm::vec3 mat_ambient = glm::vec3(0.1, 0.1, 0.1);
    glm::vec3 mat_diffuse = glm::vec3(0.5, 0.0, 0.25);
    glm::vec3 mat_specular = glm::vec3(1.0, 1.0, 1.0);
    float  mat_shineness = 40;

    float reflectance = 1.0;

    /*
    glm::vec3 point[3] = {
        glm::vec3(0.5,0.5,-1.6),
        glm::vec3(0.5,1.5,-1.6),
        glm::vec3(-0.5,1.5,-1.6)
    };
    */

    glm::vec3 point[3] = {
        glm::vec3(0.03,0.03,0.28 - 2.5),
        glm::vec3(0.10,0.03,0.45 - 2.5),
        glm::vec3(0.07,0.07,0.28 - 2.5)
    };

    bool refract = true;
    float refractivity = 1.5;
    float refractance = 1.0;

    addTriangle(++objectCount,mat_ambient,mat_diffuse,mat_specular,mat_shineness,reflectance,
        point[0],point[1],point[2], refract, refractivity, refractance);

    printObjects();

    printf("---Triangle set up OK--- \n");
}

float *Vertices = NULL;
unsigned int *Indices = NULL;

int VertexNum;
int FaceNum;

void readSMF(const char *name){
    FILE *fin = NULL;
    fin = fopen(name,"r");
    if(fin == NULL){
        printf("Error Opening the File\n");
        fclose(fin); exit(1);
    }

    if( fscanf(fin," # %d %d",&VertexNum,&FaceNum) < 2) {
        printf("Error Reading the File\n");
        fclose(fin); exit(1);
    }

    if(Vertices != NULL) delete Vertices;
    Vertices = new float [ VertexNum * 3 ];
    if(Vertices == NULL) {
        printf("Error Allocating Memory\n");
        fclose(fin); exit(1);
    }

    if(Indices != NULL) delete Indices;
    Indices = new unsigned int [ FaceNum * 3 ];
    if(Indices == NULL) {
        printf("Error Allocating Memory\n");
        fclose(fin); exit(1);
    }

    for(int i=0;i<VertexNum;i++)
        if( fscanf(fin," v %f %f %f",&Vertices[i*3], &Vertices[i*3 +1], &Vertices[i*3 +2]) < 3){
            printf("Error Reading the File\n");
            fclose(fin); exit(1);
        }

    int ta,tb,tc;
    for(int i=0;i<FaceNum;i++){
        if( fscanf(fin," f %d %d %d",&ta,&tb,&tc) < 3){
            printf("Error Reading the File\n");
            fclose(fin); exit(1);
        }
        Indices[i*3] = ta-1;
        Indices[i*3 +1] = tb-1;
        Indices[i*3 +2] = tc-1;
    }

    fclose(fin);
}

void checkMinMax(){
    float Min[3] = {100,100,100};
    float Max[3] = {0,0,0};

    for(int i=0;i<VertexNum;i++)
        for(int j=0;j<3;j++){
            Min[j] = min(Min[j], Vertices[i*3 + j]);
            Max[j] = max(Max[j], Vertices[i*3 + j]);
        }

    for(int j=0;j<3;j++){
        printf("%c : ",'x' + j);
        printf("Min : %f ; Max : %f\n",Min[j],Max[j]);
    }
}

void set_up_chessPiece(){

    const char pieceName[] = "chess_pieces/chess_piece.smf";    

    readSMF(pieceName);
    //checkMinMax();

    glm::vec3 mat_ambient = glm::vec3(0.75, 0.5, 0.5);
    glm::vec3 mat_diffuse = glm::vec3(0.1, 0.5, 0.5);
    glm::vec3 mat_specular = glm::vec3(1.0, 1.0, 1.0);
    float  mat_shineness = 40;

    float reflectance = 0.6;

    bool refract = true;
    float refractivity = 1.5;
    float refractance = 0.2;

    glm::vec3 point[3];

    for(int i=0;i<FaceNum;i++){
        for(int j=0;j<3;j++){
            int pNum = Indices[ i*3 + j];
            point[j] = glm::vec3( Vertices[ pNum*3 ] -0.22 , Vertices[ pNum*3 +1] - 0.75, Vertices[ pNum*3 +2] -1.3 );
        }
        addTriangle(++objectCount,mat_ambient,mat_diffuse,mat_specular,mat_shineness,reflectance,
            point[0],point[1],point[2], refract, refractivity, refractance);

        //if(i == 6) printObjects();
    }

    // ------------------------

    mat_ambient = glm::vec3(0.6, 0.6, 0.6);
    mat_diffuse = glm::vec3(0.7, 0.0, 0.25);
    mat_specular = glm::vec3(1.0, 1.0, 1.0);
    mat_shineness = 40;

    reflectance = 0.2;

    refractance = 0.6;


    for(int i=0;i<FaceNum;i++){
        for(int j=0;j<3;j++){
            int pNum = Indices[ i*3 + j];
            point[j] = glm::vec3( Vertices[ pNum*3 ]  , Vertices[ pNum*3 +1] - 0.75, Vertices[ pNum*3 +2] -1 );
        }
        addTriangle(++objectCount,mat_ambient,mat_diffuse,mat_specular,mat_shineness,reflectance,
            point[0],point[1],point[2], refract, refractivity, refractance);

        //if(i == 6) printObjects();
    }

    printf("---Read chessPiece OK---\n");
    printf("object Count : %d\n", objectCount);

    delete Vertices; Vertices = NULL;
    delete Indices; Indices = NULL;
}

