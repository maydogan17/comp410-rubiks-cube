//
//  Display a rotating cube, revisited with triangle list, timer callback and reshape
//
#include <stdlib.h> 
#include "Angel.h"

typedef vec4  color4;
typedef vec4  point4;

const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)
// Vertices of a unit cube centered at origin, sides aligned with axes

point4 points[24] = { //points for every cube
    point4(-0.5, -0.5,  0.5, 1.0),
    point4(-0.5,  0.5,  0.5, 1.0),
    point4(0.5,  0.5,  0.5, 1.0),
    point4(0.5, -0.5,  0.5, 1.0),
    point4(-0.5,  0.5,  0.5, 1.0),
    point4(-0.5,  0.5, -0.5, 1.0),
    point4(0.5,  0.5, -0.5, 1.0),
    point4(0.5,  0.5,  0.5, 1.0),
    point4(0.5, -0.5, -0.5, 1.0),
    point4(-0.5,  0.5, -0.5, 1.0),
    point4(0.5,  0.5, -0.5, 1.0),
    point4(-0.5, -0.5, -0.5, 1.0),
    point4(-0.5, -0.5,  0.5, 1.0),
    point4(0.5, -0.5,  0.5, 1.0),
    point4(-0.5, -0.5, -0.5, 1.0),
    point4(0.5, -0.5, -0.5, 1.0),
    point4(-0.5, -0.5,  0.5, 1.0),
    point4(-0.5,  0.5,  0.5, 1.0),
    point4(-0.5, -0.5, -0.5, 1.0),
    point4(-0.5,  0.5, -0.5, 1.0),
    point4(0.5,  0.5,  0.5, 1.0),
    point4(0.5, -0.5,  0.5, 1.0),
    point4(0.5,  0.5, -0.5, 1.0),
    point4(0.5, -0.5, -0.5, 1.0)
};


color4 colors[24] = { //colors for rubik's cube's individual cubes
    color4(1.0, 0.0, 0.0, 1.0),  // red
    color4(1.0, 0.0, 0.0, 1.0),  // red
    color4(1.0, 0.0, 0.0, 1.0),  // red
    color4(1.0, 0.0, 0.0, 1.0),  // red

    color4(0.0, 1.0, 0.0, 1.0),  // green
    color4(0.0, 1.0, 0.0, 1.0),  // green
    color4(0.0, 1.0, 0.0, 1.0),  // green
    color4(0.0, 1.0, 0.0, 1.0),  // green

    color4(0.0, 0.0, 1.0, 1.0),  // blue
    color4(0.0, 0.0, 1.0, 1.0),  // blue
    color4(0.0, 0.0, 1.0, 1.0),  // blue
    color4(0.0, 0.0, 1.0, 1.0),  // blue

    color4(1.0, 0.4, 0.0, 1.0),  // orange
    color4(1.0, 0.4, 0.0, 1.0),  // orange
    color4(1.0, 0.4, 0.0, 1.0),  // orange
    color4(1.0, 0.4, 0.0, 1.0),  // orange

    color4(1.0, 1.0, 0.0, 1.0),  // yellow
    color4(1.0, 1.0, 0.0, 1.0),  // yellow
    color4(1.0, 1.0, 0.0, 1.0),  // yellow
    color4(1.0, 1.0, 0.0, 1.0),  // yellow

    color4(1.0, 1.0, 1.0, 1.0),  // white
    color4(1.0, 1.0, 1.0, 1.0),  // white
    color4(1.0, 1.0, 1.0, 1.0),  // white
    color4(1.0, 1.0, 1.0, 1.0)  // white
};

color4 colors_lines[24] = { //colors for lines around cubes
    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0),  // black

    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0),  // black

    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0),  // black

    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0),  // black

    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0),  // black

    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0),  // black
    color4(0.0, 0.0, 0.0, 1.0)  // black
};

//these color arrays created for back buffer cubes
color4 red_colors[24] = {};
color4 green_colors[24] = {};
color4 blue_colors[24] = {};
color4 yellow_colors[24] = {};
color4 white_colors[24] = {};
color4 black_colors[24] = {};
color4 fuchsia_colors[24] = {};
color4 aqua_colors[24] = {};

// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int  Axis = Xaxis;
GLfloat  Theta[NumAxes] = { 0.0, 0.0, 0.0 };

// Model-view and projection matrices uniform location
GLuint  ModelView, Projection;
GLuint vColor;
GLuint general_model_view; //general model view used for rotating cube with mouse movement

//----------------------------------------------------------------------------
GLuint vao[8]; //vao for individual cubes
GLuint buffer[8]; //buffer for individual cubes

GLuint back_vao[8]; //vao for back buffer cubes
GLuint back_buffer[8]; //buffer for back buffer cubes

GLuint vao_lines[8]; //vao for lines
GLuint buffer_lines[8]; //buffer for lines

mat4 model_view_arr[8]; //model view array for individual cubes
mat4 model_view_arr_lines[8]; //model view array for lines
mat4 model_view_arr_back[8]; //model view array for back buffer cubes

mat4 g_model_view; //general model view

vec3 startVector; //start vector for mouse rotation
vec3 endVector; //end vector for mouse rotation
bool rotating; //rotation flag
vec3 rotationAxis; //rotation axis
float angle; //rotation angle
mat4 rotation; //rotation matrix

int choosen_cube = 0; //flag for cube chosen by player
int choosen_axis = 0; //flag for axis chosen by player
int choosen_way = 0; //flag for negatif or positive way chosen by player


//every cube is numbered from 0 to 8
//their positions is kept in positions array
int positions[6][4];

//their positions also kept in these individual arrays
int frontZ[4] = { 2, 3, 6, 7 };
int backZ[4] = { 0, 1, 4, 5 };
int leftX[4] = { 0, 2, 4, 6 };
int rightX[4] = { 3, 1, 7, 5 };
int topY[4] = { 0, 1, 2, 3 };
int bottomY[4] = { 4, 5, 6, 7 };

//flag for executing rotation animation
bool execute_rotation = false;

//above color arrays for back buffer cubes filled here
void
color_array_filler()
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 24; j++) {
            color4 insert;
            switch (i) {
            case 0:  insert = color4(1.0, 0.0, 0.0, 1.0); red_colors[j] = insert;   break;  //red
            case 1:  insert = color4(0.0, 1.0, 0.0, 1.0); green_colors[j] = insert;  break;  //green
            case 2:  insert = color4(0.0, 0.0, 1.0, 1.0); blue_colors[j] = insert;  break;  //blue
            case 3:  insert = color4(1.0, 1.0, 0.0, 1.0); yellow_colors[j] = insert;  break;  //yellow
            case 4:  insert = color4(1.0, 1.0, 1.0, 1.0); white_colors[j] = insert;  break;  //white
            case 5:  insert = color4(0.0, 0.0, 0.0, 1.0); black_colors[j] = insert;  break;  //black
            case 6:  insert = color4(1.0, 0.0, 1.0, 1.0); fuchsia_colors[j] = insert;  break;  //fuchsia 
            case 7:  insert = color4(0.0, 1.0, 1.0, 1.0); aqua_colors[j] = insert;  break;  //aqua
            }
        }
    }
}

//cube positions written onto positions array here
void
updatePositions() {
    positions[0][0] = frontZ[0];
    positions[0][1] = frontZ[1];
    positions[0][2] = frontZ[2];
    positions[0][3] = frontZ[3];

    positions[1][0] = backZ[0];
    positions[1][1] = backZ[1];
    positions[1][2] = backZ[2];
    positions[1][3] = backZ[3];

    positions[2][0] = leftX[0];
    positions[2][1] = leftX[1];
    positions[2][2] = leftX[2];
    positions[2][3] = leftX[3];

    positions[3][0] = rightX[0];
    positions[3][1] = rightX[1];
    positions[3][2] = rightX[2];
    positions[3][3] = rightX[3];

    positions[4][0] = topY[0];
    positions[4][1] = topY[1];
    positions[4][2] = topY[2];
    positions[4][3] = topY[3];

    positions[5][0] = bottomY[0];
    positions[5][1] = bottomY[1];
    positions[5][2] = bottomY[2];
    positions[5][3] = bottomY[3];
}


// OpenGL initialization
void
init()
{
    srand(time(NULL)); //random seed
    color_array_filler(); //collor arrays filled
    updatePositions(); //positions array initialized

    GLuint cube_indices[] = {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        8, 10, 9,
        9, 11, 8,
        14, 12, 13,
        13, 15, 14,
        18, 19, 17,
        17, 16, 18,
        21, 20, 22,
        22, 23, 21
    };

    GLuint line_indices[] = {
        0,1,
        1,2,
        2,3,
        3,0,

        4,5,
        5,6,
        6,7,
        7,4,

        8,10,
        10,9,
        9,11,
        11,8,

        14,12,
        12,13,
        13,15,
        15,14,

        18,19,
        19,17,
        17,16,
        16,18,

        21,20,
        20,22,
        22,23,
        23,21
    };
    // Load shaders and use the resulting shader program
    GLuint program = InitShader("C:/Users/MAYDOGAN17/OneDrive - Koc Universitesi/Masaüstü/KU/9-SPRING 2022/COMP410/HW2/vshader.glsl",
        "C:/Users/MAYDOGAN17/OneDrive - Koc Universitesi/Masaüstü/KU/9-SPRING 2022/COMP410/HW2/fshader.glsl");


    // Create a vertex array object
    // Create and initialize a vertex buffer object
    glGenVertexArrays(8, vao);

    //cubes
    for (int i = 0; i < 8; i++) {
        glBindVertexArray(vao[i]);

        glGenBuffers(1, &buffer[i]);
        glBindBuffer(GL_ARRAY_BUFFER, buffer[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);


        // Create and initialize an index buffer object
        GLuint index_buffer;
        glGenBuffers(1, &index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


        // set up vertex arrays
        GLuint vPosition = glGetAttribLocation(program, "vPosition");
        glEnableVertexAttribArray(vPosition);
        glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

        vColor = glGetAttribLocation(program, "vColor");
        glEnableVertexAttribArray(vColor);
        glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));
    }
    //lines
    glGenVertexArrays(8, vao_lines);

    for (int i = 0; i < 8; i++) {
        glBindVertexArray(vao_lines[i]);

        glGenBuffers(1, &buffer_lines[i]);
        glBindBuffer(GL_ARRAY_BUFFER, buffer_lines[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors_lines), NULL, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors_lines), colors_lines);


        // Create and initialize an index buffer object
        GLuint index_buffer;
        glGenBuffers(1, &index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(line_indices), line_indices, GL_STATIC_DRAW);


        // set up vertex arrays
        GLuint vPosition = glGetAttribLocation(program, "vPosition");
        glEnableVertexAttribArray(vPosition);
        glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

        vColor = glGetAttribLocation(program, "vColor");
        glEnableVertexAttribArray(vColor);
        glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));
    }
    //back buffer cubes for selection
    glGenVertexArrays(8, back_vao);

    for (int i = 0; i < 8; i++) {
        glBindVertexArray(back_vao[i]);

        glGenBuffers(1, &back_buffer[i]);
        glBindBuffer(GL_ARRAY_BUFFER, back_buffer[i]);

        //all have different colors
        switch (i) {
        case 0:  glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(red_colors), NULL, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(red_colors), red_colors);   break;  //red
        case 1:  glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(green_colors), NULL, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(green_colors), green_colors);  break;  //green
        case 2:  glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(blue_colors), NULL, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(blue_colors), blue_colors);  break;  //blue
        case 3:  glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(yellow_colors), NULL, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(yellow_colors), yellow_colors);  break;  //yellow
        case 4:  glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(white_colors), NULL, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(white_colors), white_colors);  break;  //white
        case 5:  glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(black_colors), NULL, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(black_colors), black_colors);  break;  //black
        case 6:  glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(fuchsia_colors), NULL, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(fuchsia_colors), fuchsia_colors);  break;  //fuchsia 
        case 7:  glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(aqua_colors), NULL, GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
            glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(aqua_colors), aqua_colors);  break;  //aqua
        }

        // Create and initialize an index buffer object
        GLuint index_buffer;
        glGenBuffers(1, &index_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


        // set up vertex arrays
        GLuint vPosition = glGetAttribLocation(program, "vPosition");
        glEnableVertexAttribArray(vPosition);
        glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

        vColor = glGetAttribLocation(program, "vColor");
        glEnableVertexAttribArray(vColor);
        glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));
    }
        
    // Retrieve transformation uniform variable locations
    ModelView = glGetUniformLocation( program, "ModelView" );
    Projection = glGetUniformLocation( program, "Projection" );

    general_model_view = glGetUniformLocation(program, "GeneralModelView");
    
    mat4  projection;
    projection = Perspective( 75.0, 1.0, 0.1, 1000.0 ); //try also perspective projection instead of ortho
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
    
    // Set current program object
    glUseProgram( program );
    
    // Enable hiddden surface removal
    glEnable( GL_DEPTH_TEST );
    
    // Set state variable "clear color" to clear buffer with.
    glClearColor( 0.0, 0.0, 0.0, 1.0 );

    //every elements initial position set here
    for (int i = 0; i < 8; i++) {
        vec3 displacement(0.0, 0.0, -5);
        vec3 displacement2(0.0, 0.0, 0.5);
        switch (i) {
        case 0:   displacement.y = 0.5; displacement.x = -0.5;  break;
        case 1:   displacement.y = 0.5; displacement.x = 0.5;  break;
        case 2:   displacement.y = 0.5; displacement.x = -0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 3:   displacement.y = 0.5; displacement.x = 0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 4:   displacement.y = -0.5; displacement.x = -0.5;  break;
        case 5:   displacement.y = -0.5; displacement.x = 0.5;  break;
        case 6:   displacement.y = -0.5; displacement.x = -0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 7:   displacement.y = -0.5; displacement.x = 0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        }

        displacement2.x = -displacement.x;
        displacement2.y = -displacement.y;

        model_view_arr[i] = (Translate(displacement) * Scale(1.0, 1.0, 1.0));
    }
    for (int i = 0; i < 8; i++) {
        vec3 displacement(0.0, 0.0, -5);
        vec3 displacement2(0.0, 0.0, 0.5);
        switch (i) {
        case 0:   displacement.y = 0.5; displacement.x = -0.5;  break;
        case 1:   displacement.y = 0.5; displacement.x = 0.5;  break;
        case 2:   displacement.y = 0.5; displacement.x = -0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 3:   displacement.y = 0.5; displacement.x = 0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 4:   displacement.y = -0.5; displacement.x = -0.5;  break;
        case 5:   displacement.y = -0.5; displacement.x = 0.5;  break;
        case 6:   displacement.y = -0.5; displacement.x = -0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 7:   displacement.y = -0.5; displacement.x = 0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        }

        displacement2.x = -displacement.x;
        displacement2.y = -displacement.y;

        model_view_arr_lines[i] = (Translate(displacement) * Scale(1.0, 1.0, 1.0));
    }
    for (int i = 0; i < 8; i++) {
        vec3 displacement(0.0, 0.0, -5);
        vec3 displacement2(0.0, 0.0, 0.5);
        switch (i) {
        case 0:   displacement.y = 0.5; displacement.x = -0.5;  break;
        case 1:   displacement.y = 0.5; displacement.x = 0.5;  break;
        case 2:   displacement.y = 0.5; displacement.x = -0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 3:   displacement.y = 0.5; displacement.x = 0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 4:   displacement.y = -0.5; displacement.x = -0.5;  break;
        case 5:   displacement.y = -0.5; displacement.x = 0.5;  break;
        case 6:   displacement.y = -0.5; displacement.x = -0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 7:   displacement.y = -0.5; displacement.x = 0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        }

        displacement2.x = -displacement.x;
        displacement2.y = -displacement.y;

        model_view_arr_back[i] = (Translate(displacement) * Scale(1.0, 1.0, 1.0));
    }

   }

//----------------------------------------------------------------------------
//self explanatory
bool
contains(int arr[], int arr_size, int element) {
    for (int i = 0; i < arr_size; i++) {
        if (arr[i] == element) {
            return true;
        }
    }
    return false;
}
//below you will find series of function to be used after every rotation execution
//after every execution cubes positions in the arrays needs to be updated
//first their positions within their relative group updated
//secondly other effected arrays updated
void
update_for_leftX() {
    if (choosen_way == 0) {
        int before0 = leftX[0];
        int before1 = leftX[1];
        int before2 = leftX[2];
        int before3 = leftX[3];

        leftX[0] = before2;
        leftX[1] = before0;
        leftX[2] = before3;
        leftX[3] = before1;
    }
    else {
        int before0 = leftX[0];
        int before1 = leftX[1];
        int before2 = leftX[2];
        int before3 = leftX[3];

        leftX[0] = before1;
        leftX[1] = before3;
        leftX[2] = before0;
        leftX[3] = before2;
    }
}
void
update_after_leftX() {
    topY[0] = leftX[0];
    topY[2] = leftX[1];

    bottomY[0] = leftX[2];
    bottomY[2] = leftX[3];

    frontZ[0] = leftX[1];
    frontZ[2] = leftX[3];

    backZ[0] = leftX[0];
    backZ[2] = leftX[2];
}
void
update_for_rightX() {
    if (choosen_way == 0) {
        int before0 = rightX[0];
        int before1 = rightX[1];
        int before2 = rightX[2];
        int before3 = rightX[3];

        rightX[0] = before1;
        rightX[1] = before3;
        rightX[2] = before0;
        rightX[3] = before2;
    }
    else {
        int before0 = rightX[0];
        int before1 = rightX[1];
        int before2 = rightX[2];
        int before3 = rightX[3];

        rightX[0] = before2;
        rightX[1] = before0;
        rightX[2] = before3;
        rightX[3] = before1;
    }
}
void
update_after_rightX() {
    topY[1] = rightX[1];
    topY[3] = rightX[0];

    bottomY[3] = rightX[2];
    bottomY[1] = rightX[3];

    frontZ[1] = rightX[0];
    frontZ[3] = rightX[2];

    backZ[1] = rightX[1];
    backZ[3] = rightX[3];
}
void
update_for_topY() {
    if (choosen_way == 0) {
        int before0 = topY[0];
        int before1 = topY[1];
        int before2 = topY[2];
        int before3 = topY[3];

        topY[0] = before1;
        topY[1] = before3;
        topY[2] = before0;
        topY[3] = before2;
    }
    else {
        int before0 = topY[0];
        int before1 = topY[1];
        int before2 = topY[2];
        int before3 = topY[3];

        topY[0] = before2;
        topY[1] = before0;
        topY[2] = before3;
        topY[3] = before1;
    }
}
void
update_after_topY() {
    leftX[0] = topY[0];
    leftX[1] = topY[2];

    rightX[0] = topY[3];
    rightX[1] = topY[1];

    frontZ[0] = topY[2];
    frontZ[1] = topY[3];

    backZ[0] = topY[0];
    backZ[1] = topY[1];
}

void
update_for_bottomY() {
    if (choosen_way == 0) {
        int before0 = bottomY[0];
        int before1 = bottomY[1];
        int before2 = bottomY[2];
        int before3 = bottomY[3];

        bottomY[0] = before1;
        bottomY[1] = before3;
        bottomY[2] = before0;
        bottomY[3] = before2;
    }
    else {
        int before0 = bottomY[0];
        int before1 = bottomY[1];
        int before2 = bottomY[2];
        int before3 = bottomY[3];

        bottomY[0] = before2;
        bottomY[1] = before0;
        bottomY[2] = before3;
        bottomY[3] = before1;
    }
}
void
update_after_bottomY() {
    leftX[2] = bottomY[0];
    leftX[3] = bottomY[2];

    rightX[3] = bottomY[1];
    rightX[2] = bottomY[3];

    frontZ[2] = bottomY[2];
    frontZ[3] = bottomY[3];

    backZ[2] = bottomY[0];
    backZ[3] = bottomY[1];
}

void
update_for_frontZ() {
    if (choosen_way == 0) {
        int before0 = frontZ[0];
        int before1 = frontZ[1];
        int before2 = frontZ[2];
        int before3 = frontZ[3];

        frontZ[0] = before1;
        frontZ[1] = before3;
        frontZ[2] = before0;
        frontZ[3] = before2;
    }
    else {
        int before0 = frontZ[0];
        int before1 = frontZ[1];
        int before2 = frontZ[2];
        int before3 = frontZ[3];

        frontZ[0] = before2;
        frontZ[1] = before0;
        frontZ[2] = before3;
        frontZ[3] = before1;
    }
}
void
update_after_frontZ() {
    leftX[1] = frontZ[0];
    leftX[3] = frontZ[2];

    rightX[0] = frontZ[1];
    rightX[2] = frontZ[3];

    topY[2] = frontZ[0];
    topY[3] = frontZ[1];

    bottomY[2] = frontZ[2];
    bottomY[3] = frontZ[3];
}

void
update_for_backZ() {
    if (choosen_way == 0) {
        int before0 = backZ[0];
        int before1 = backZ[1];
        int before2 = backZ[2];
        int before3 = backZ[3];

        backZ[0] = before1;
        backZ[1] = before3;
        backZ[2] = before0;
        backZ[3] = before2;
    }
    else {
        int before0 = backZ[0];
        int before1 = backZ[1];
        int before2 = backZ[2];
        int before3 = backZ[3];

        backZ[0] = before2;
        backZ[1] = before0;
        backZ[2] = before3;
        backZ[3] = before1;
    }
}
void
update_after_backZ() {
    leftX[0] = backZ[0];
    leftX[2] = backZ[2];

    rightX[1] = backZ[1];
    rightX[3] = backZ[3];

    topY[0] = backZ[0];
    topY[1] = backZ[1];

    bottomY[0] = backZ[2];
    bottomY[1] = backZ[3];
}

//executeRotation function tells display function to which positions array to be used
//it also sets Axis
int
executeRotation() {
    if (choosen_axis == 0) {
        if (contains(leftX, 4, choosen_cube)) {
            Axis = Xaxis;
            return 2;
        }
        else {
            Axis = Xaxis;
            return 3;
            
        }
    }
    else if (choosen_axis == 1) {
        if (contains(topY, 4, choosen_cube)) {
            Axis = Yaxis;
            return 4;
        }
        else {
            Axis = Yaxis;
            return 5;
        }
    }
    else {
        if (contains(frontZ, 4, choosen_cube)) {
            Axis = Zaxis;
            return 0;
        }
        else {
            Axis = Zaxis;
            return 1;
        }
    }
}

void
display( void )
{
    mat4 randMat;
    randMat = Perspective(120.0, 1.0, 2.0, 3.0);
    mat4 randMat3 = Frustum(-3.46, 3.46, -3.46, 3.46, -2.0, -3.0);
    mat4 randMat4 = Frustum(-0.577, 0.577, -0.577, 0.577, -2.0, -3.0);
    vec3 dis = vec3(0, 0, 1);
    //randMat = Translate(-dis) * randMat * Translate(dis);
    mat4 randMat2;
    randMat2 = Ortho(2.0, 5.0, 1.0, 2.0, 2.0, 4.0);
    //printm(randMat);
    //cubes
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (int i = 0; i < 8; i++) {
        vec3 displacement(0.0, 0.0, -5);
        vec3 displacement2(0.0, 0.0, 0.5);
        switch (i) {
        case 0:   displacement.y = 0.5; displacement.x = -0.5;  break;
        case 1:   displacement.y = 0.5; displacement.x = 0.5;  break;
        case 2:   displacement.y = 0.5; displacement.x = -0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 3:   displacement.y = 0.5; displacement.x = 0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 4:   displacement.y = -0.5; displacement.x = -0.5;  break;
        case 5:   displacement.y = -0.5; displacement.x = 0.5;  break;
        case 6:   displacement.y = -0.5; displacement.x = -0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 7:   displacement.y = -0.5; displacement.x = 0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        }
        
        displacement2.x = -displacement.x;
        displacement2.y = -displacement.y;

        //if execute_rotation flag is true, display function rotates the model_views that needs to be rotated
        if (execute_rotation) {
            int arr_num = executeRotation();
            bool isRotate = false;
            for (int j = 0; j < 4; j++) {
                if (positions[arr_num][j] == i) {
                    isRotate = true;
                }
            }   
            if (isRotate) {
                 model_view_arr[i] = (Translate(displacement2)  * Translate(displacement) *
                     RotateX(Theta[Xaxis]) *
                     RotateY(Theta[Yaxis]) *
                     RotateZ(Theta[Zaxis]) * Translate(-displacement) * Translate(-displacement2) * model_view_arr[i]);
            }
        }

        g_model_view = (Translate(displacement2)* Translate(displacement) * rotation * Translate(-displacement) * Translate(-displacement2));
        glUniformMatrix4fv(general_model_view, 1, GL_TRUE, g_model_view);

        glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view_arr[i]);
        glBindVertexArray(vao[i]);
        glDrawElements(GL_TRIANGLES, NumVertices, GL_UNSIGNED_INT, 0);
    }
    //lines
    for (int i = 0; i < 8; i++) {
        vec3 displacement(0.0, 0.0, -5);
        vec3 displacement2(0.0, 0.0, 0.5);
        switch (i) {
        case 0:   displacement.y = 0.5; displacement.x = -0.5;  break;
        case 1:   displacement.y = 0.5; displacement.x = 0.5;  break;
        case 2:   displacement.y = 0.5; displacement.x = -0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 3:   displacement.y = 0.5; displacement.x = 0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 4:   displacement.y = -0.5; displacement.x = -0.5;  break;
        case 5:   displacement.y = -0.5; displacement.x = 0.5;  break;
        case 6:   displacement.y = -0.5; displacement.x = -0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 7:   displacement.y = -0.5; displacement.x = 0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        }

        displacement2.x = -displacement.x;
        displacement2.y = -displacement.y;


        if (execute_rotation) {
            int arr_num = executeRotation();
            bool isRotate = false;
            for (int j = 0; j < 4; j++) {
                if (positions[arr_num][j] == i) {
                    isRotate = true;
                }
            }
            if (isRotate) {
                model_view_arr_lines[i] = (Translate(displacement2) * Translate(displacement) *
                    RotateX(Theta[Xaxis]) *
                    RotateY(Theta[Yaxis]) *
                    RotateZ(Theta[Zaxis]) * Translate(-displacement) * Translate(-displacement2) * model_view_arr_lines[i]);
            }
        }


        g_model_view = (Translate(displacement2) * Translate(displacement) * rotation * Translate(-displacement) * Translate(-displacement2));
        glUniformMatrix4fv(general_model_view, 1, GL_TRUE, g_model_view);

        glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view_arr_lines[i]);
        glBindVertexArray(vao_lines[i]);
        glLineWidth(3.0);
        glDrawElements(GL_LINES, NumVertices, GL_UNSIGNED_INT, 0);
    }
    //back buffer cubes
    for (int i = 0; i < 8; i++) {
        vec3 displacement(0.0, 0.0, -5);
        vec3 displacement2(0.0, 0.0, 0.5);
        switch (i) {
        case 0:   displacement.y = 0.5; displacement.x = -0.5;  break;
        case 1:   displacement.y = 0.5; displacement.x = 0.5;  break;
        case 2:   displacement.y = 0.5; displacement.x = -0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 3:   displacement.y = 0.5; displacement.x = 0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 4:   displacement.y = -0.5; displacement.x = -0.5;  break;
        case 5:   displacement.y = -0.5; displacement.x = 0.5;  break;
        case 6:   displacement.y = -0.5; displacement.x = -0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        case 7:   displacement.y = -0.5; displacement.x = 0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
        }

        displacement2.x = -displacement.x;
        displacement2.y = -displacement.y;

        if (execute_rotation) {
            int arr_num = executeRotation();
            bool isRotate = false;
            for (int j = 0; j < 4; j++) {
                if (positions[arr_num][j] == i) {
                    isRotate = true;
                }
            }
            if (isRotate) {
                model_view_arr_back[i] = (Translate(displacement2) * Translate(displacement) *
                    RotateX(Theta[Xaxis]) *
                    RotateY(Theta[Yaxis]) *
                    RotateZ(Theta[Zaxis]) * Translate(-displacement) * Translate(-displacement2) * model_view_arr_back[i]);
            }
        }

        g_model_view = (Translate(displacement2) * Translate(displacement) * rotation * Translate(-displacement) * Translate(-displacement2));
        glUniformMatrix4fv(general_model_view, 1, GL_TRUE, g_model_view);

        glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view_arr_back[i]);
        glBindVertexArray(back_vao[i]);
        //glDrawElements(GL_TRIANGLES, NumVertices, GL_UNSIGNED_INT, 0);
        //to display back buffer cubes uncomment above line and comment cubes draw function
    }
    glutSwapBuffers();
    
}



//---------------------------------------------------------------------
//
// reshape
//

void reshape( int w, int h )
{
    glViewport( 0, 0, w, h );
    
    // Set projection matrix
    mat4  projection;
    if (w <= h) {
        projection = Perspective(75, (GLfloat)w / (GLfloat)w, 0.1, 1000.0);
        glViewport(0, h / 2 - w / 2, w, w);
    }
    else  projection = Perspective(75, (GLfloat)w / (GLfloat)h, 0.1, 1000.0);

    glUniformMatrix4fv(Projection, 1, GL_TRUE, projection);
    //reshape callback needs to be changed if perspective prohection is used
}

double RadiansToDegrees(double radian)
{
    double pi = 3.14159;
    return(radian * (180 / pi));
}

void startRotation(int xPos, int yPos) {

    // xy normalized device coordinates:
    float ndcX = 2.0f * xPos / glutGet(GLUT_WINDOW_WIDTH) - 1.0f;
    float ndcY = 1.0 - 2.0f * yPos / glutGet(GLUT_WINDOW_HEIGHT);

    startVector = vec3(ndcX, ndcY, 0.0);
    endVector = startVector;
    rotating = true; //set rotating flag to true
}

void updateRotation(int xPos, int yPos) {

    if (rotating) {
        // xy normalized device coordinates:
        float ndcX = 2.0f * xPos / glutGet(GLUT_WINDOW_WIDTH) - 1.0f;
        float ndcY = 1.0 - 2.0f * yPos / glutGet(GLUT_WINDOW_HEIGHT);

        endVector = vec3(ndcX, ndcY, 0.0);

        vec3 direction = endVector - startVector; //vector created from mouse's movement
        rotationAxis = normalize(vec3(-direction.y, direction.x, 0.0)); // normatize the direction of the movement
        angle = (float)RadiansToDegrees(length(direction) * 3.141593); // length of the movement vector is the angle

        mat4 addRotation; // rotation matrix
        float angleY = (float)(angle * rotationAxis.y);
        float angleX = (float)(angle * rotationAxis.x);
        addRotation = RotateX(angleX);
        addRotation.operator*=(RotateY(angleY));
        rotation = addRotation * rotation;

        startVector = endVector;
    }

}


//----------------------------------------------------------------------------

void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
        startRotation(x, y);  //initial left click starts the rotation
    }
    if (state == GLUT_UP && button == GLUT_LEFT_BUTTON) {
        rotating = false; //when user stop clicking down to left button rotation stops
    }
    if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON) { //right button used for picking
        rotating = false; //when picking a cube rotation needs to be stopped
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //back buffer cubes initialized
        for (int i = 0; i < 8; i++) {
            vec3 displacement(0.0, 0.0, -5);
            vec3 displacement2(0.0, 0.0, 0.5);
            switch (i) {
            case 0:   displacement.y = 0.5; displacement.x = -0.5;  break;
            case 1:   displacement.y = 0.5; displacement.x = 0.5;  break;
            case 2:   displacement.y = 0.5; displacement.x = -0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
            case 3:   displacement.y = 0.5; displacement.x = 0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
            case 4:   displacement.y = -0.5; displacement.x = -0.5;  break;
            case 5:   displacement.y = -0.5; displacement.x = 0.5;  break;
            case 6:   displacement.y = -0.5; displacement.x = -0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
            case 7:   displacement.y = -0.5; displacement.x = 0.5; displacement.z = -4.0; displacement2.z = -0.5;  break;
            }

            displacement2.x = -displacement.x;
            displacement2.y = -displacement.y;

            if (execute_rotation) {
                int arr_num = executeRotation();
                bool isRotate = false;
                for (int j = 0; j < 4; j++) {
                    if (positions[arr_num][j] == i) {
                        isRotate = true;
                    }
                }
                if (isRotate) {
                    model_view_arr_back[i] = (Translate(displacement2) * Translate(displacement) *
                        RotateX(Theta[Xaxis]) *
                        RotateY(Theta[Yaxis]) *
                        RotateZ(Theta[Zaxis]) * Translate(-displacement) * Translate(-displacement2) * model_view_arr_back[i]);
                }
            }

            g_model_view = (Translate(displacement2) * Translate(displacement) * rotation * Translate(-displacement) * Translate(-displacement2));
            glUniformMatrix4fv(general_model_view, 1, GL_TRUE, g_model_view);

            glUniformMatrix4fv(ModelView, 1, GL_TRUE, model_view_arr_back[i]);
            glBindVertexArray(back_vao[i]);
            glDrawElements(GL_TRIANGLES, NumVertices, GL_UNSIGNED_INT, 0);
        }

        glFlush();

        //back buffer cubes special colors used for picking
        y = glutGet(GLUT_WINDOW_HEIGHT) - y;

        unsigned char pixel[4];
        glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

        if (pixel[0] == 255 && pixel[1] == 0 && pixel[2] == 0) {
            std::cout << "red cube" << std::endl;
            choosen_cube = 0;
        }
        else if (pixel[0] == 0 && pixel[1] == 255 && pixel[2] == 0) {
            std::cout << "green cube" << std::endl;
            choosen_cube = 1;
        }
        else if (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 255) {
            std::cout << "blue cube" << std::endl;
            choosen_cube = 2;
        }
        else if (pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 0) {
            std::cout << "yellow cube" << std::endl;
            choosen_cube = 3;
        }
        else if (pixel[0] == 255 && pixel[1] == 255 && pixel[2] == 255) {
            std::cout << "white cube" << std::endl;
            choosen_cube = 4;
        }
        else if (pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0) {
            std::cout << "black cube" << std::endl;
            choosen_cube = 5;
        }
        else if (pixel[0] == 255 && pixel[1] == 0 && pixel[2] == 255) {
            std::cout << "fuchsia cube" << std::endl;
            choosen_cube = 6;
        }
        else if (pixel[0] == 0 && pixel[1] == 255 && pixel[2] == 255) {
            std::cout << "aqua cube" << std::endl;
            choosen_cube = 7;
        }
        else std::cout << "None" << std::endl;

        std::cout << choosen_cube << std::endl;

        std::cout << "R: " << (int)pixel[0] << std::endl;
        std::cout << "G: " << (int)pixel[1] << std::endl;
        std::cout << "B: " << (int)pixel[2] << std::endl;
        std::cout << std::endl;
        //glutSwapBuffers();
        //uncomment above line to observe back buffer
    }
}

//----------------------------------------------------------------------------

//final updater called after rotation animation to handle cube positions change on arrays
void
finalUpdater() {
    switch (executeRotation()) {
    case 0:   update_for_frontZ(); update_after_frontZ(); updatePositions(); break;
    case 1:   update_for_backZ(); update_after_backZ(); updatePositions();   break;
    case 2:   update_for_leftX(); update_after_leftX(); updatePositions();   break;
    case 3:   update_for_rightX(); update_after_rightX(); updatePositions(); break;
    case 4:   update_for_topY(); update_after_topY(); updatePositions();     break;
    case 5:   update_for_bottomY(); update_after_bottomY(); updatePositions(); break;
    }

    //std::cout << "---------------------------------" << std::endl;
    //for (int i = 0; i < 6; i++) {
    //    std::cout << "****" << std::endl;
    //    for (int j = 0; j < 4; j++) {
    //        std::cout << positions[i][j] << std::endl;
    //    }
    //}
    //std::cout << "---------------------------------" << std::endl;

    //uncomment above part to observe cube position arrays
}

//cubes rotated 5 degree every frame, when they rotated total of 90 degrees animation stops

int totalDegree = 0;
void
smoothAnimation() {
    if (execute_rotation) {
        if (totalDegree >= 90 && choosen_way == 0) {
            execute_rotation = false;
            Theta[Axis] = 0;
            totalDegree = 0;
            finalUpdater();
            //after animation stopped arrays handled in finalUpdater and execute_rotation flag turned to false
        }
        else if (totalDegree <= -90 && choosen_way == 1) {
            execute_rotation = false;
            Theta[Axis] = 0;
            totalDegree = 0;
            finalUpdater(); 
        }
        else {
            if (choosen_way == 0) {
                Theta[Axis] = 5.0;
                totalDegree += 5;
            }
            else {
                Theta[Axis] = -5.0;
                totalDegree += -5;
            }
        }
    }
}

//randomize cube executes a single random move
void
randomizeCube() {
    int choosen_a = rand() % 3;
    int choosen_c = rand() % 8;
    int choosen_w = rand() % 2;
    
    choosen_cube = choosen_c;
    choosen_axis = choosen_a;
    choosen_way = choosen_w;

    executeRotation();

    execute_rotation = true;
}
void
print_helper() {
    printf("--------------------------------------------------------------------\n");
    printf("|Welcome to helper!\n|\tTo rotate the cube press and hold left mouse click\n|\tTo pick a cube to rotate use right mouse button\n|\tTo rotate around X axis press 'x'\n");
    printf("|\tTo rotate around Y axis press 'y'\n|\tTo rotate around Z axis press 'z'\n|\tTo rotate with negative direction press 'n'\n");
    printf("|\tTo rotate with positive direction press 'p'\n|\tTo execute the rotation press 'e'\n|\tTo execute a random rotation press 'r'\n");
    printf("|\tTo open helper press 'h'\n|\tTo close the program press 'q'\n");
    printf("|\tIMPORTANT NOTE!\n|\t\tAfter pressing 'r' or 'e', please wait untill the animation is comleted.\n|\t\tOtherwise you will witness some funny things :)\n");
    printf("--------------------------------------------------------------------\n\n");

}

void
keyboard(unsigned char key, int x, int y)
{
    if (key == 'Q' | key == 'q')
        exit(0);
    if (key == 'X' | key == 'x') {
        Axis = Xaxis;
        choosen_axis = 0;
    }
    if (key == 'Y' | key == 'y') {
        Axis = Yaxis;
        choosen_axis = 1;
    }
    if (key == 'Z' | key == 'z') {
        Axis = Zaxis;
        choosen_axis = 2;
    }
    if (key == 'P' | key == 'p') {
        choosen_way = 0;
    }
    if (key == 'N' | key == 'n') {
        choosen_way = 1;
    }
    if (key == 'E' | key == 'e') {
        execute_rotation = true;   
    }
    if (key == 'R' | key == 'r') {
        randomizeCube();   
    }
    if (key == 'H' | key == 'h')
        print_helper();

}

void timer( int p )
{
    smoothAnimation();

    glutPostRedisplay();
    
    glutTimerFunc(20,timer,0);
}


//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode(  GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize( 800, 800 );
    glutInitWindowPosition( 50, 50 );
    glutCreateWindow( "Rubik's Cube" );
    
    glewExperimental = GL_TRUE;
    glewInit();

    init();
    
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutMouseFunc(mouse);
    glutMotionFunc(updateRotation);
    glutKeyboardFunc(keyboard);
    
    glutTimerFunc(20,timer,0);
    
    glutMainLoop();
    return 0;
}

