/*
 * Description: implementation of object.hpp
 * Author: HBF
 * Version: 2021-08-24
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "object.hpp"

//Create Node
NODE* createNode(SHAPE *object) {
    NODE *newNode = (NODE*)malloc(sizeof(NODE));
    if (newNode == NULL) {
        //printf("Error: Could not allocate memory for new node\n");
        exit(1);
    }
    newNode->object = object;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}


// Define the objList variable
LIST objList;

// Define the initializeList function
void initializeList() {
    objList.start = NULL;  // Set the start of the list to NULL
    objList.end = NULL;    // Set the end of the list to NULL
}


void insert(LIST *list, SHAPE *object) {
    NODE *newNode = createNode(object);
    if (list->start == NULL) { // If the list is empty
        list->start = newNode;
        list->end = newNode;
    } else { // If the list is not empty
        newNode->prev = list->end;
        list->end->next = newNode;
        list->end = newNode;
    }
}

void deleteNode(LIST *list, NODE **selectp) {
    NODE *select = *selectp;

    if (select == NULL) {
        return;
    }

    if (select == list->start && select == list->end) { // Only one node in the list
        list->start = list->end = NULL;
    } else if (select == list->start) { // Node to be deleted is the first node
        list->start = select->next;
        list->start->prev = NULL;
    } else if (select == list->end) { // Node to be deleted is the last node
        list->end = select->prev;
        list->end->next = NULL;
    } else { // Node to be deleted is in the middle
        select->prev->next = select->next;
        select->next->prev = select->prev;
    }

    free(select->object); // Free the shape object
    free(select);         // Free the node itself
    *selectp = NULL;      // Set the pointer to NULL
}

void clearList(LIST *list) {
    NODE *current = list->start;
    NODE *next;

    while (current != NULL) {
        next = current->next;
        free(current->object); // Free the shape object
        free(current);         // Free the node
        current = next;
    }

    list->start = list->end = NULL;
}


void drawRectangle(SHAPE *object) {
    // Filled rectangle
    glColor3f(object->fr, object->fg, object->fb);
    glBegin(GL_QUADS);
    glVertex2i(object->x1, object->y1);
    glVertex2i(object->x2, object->y1);
    glVertex2i(object->x2, object->y2);
    glVertex2i(object->x1, object->y2);
    glEnd();

    // Rectangle outline
    glColor3f(object->sr, object->sg, object->sb);
    glLineWidth(object->swidth);
    glBegin(GL_LINE_LOOP);
    glVertex2i(object->x1, object->y1);
    glVertex2i(object->x2, object->y1);
    glVertex2i(object->x2, object->y2);
    glVertex2i(object->x1, object->y2);
    glEnd();
}


// Function to draw a filled circle and its outline
void drawCircle(SHAPE *object) {
    // Calculate radius from the center (x1, y1) and a point on the circumference (x2, y2)
    float radius = sqrtf(powf(object->x2 - object->x1, 2) + powf(object->y2 - object->y1, 2));
    int segments = 100; // Number of segments to approximate the circle
    float angleStep = 2.0f * M_PI / segments;

    // Filled circle
    glColor3f(object->fr, object->fg, object->fb);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(object->x1, object->y1); // Center of the circle
    for (int i = 0; i <= segments; i++) {
        float angle = i * angleStep;
        glVertex2f(object->x1 + radius * cosf(angle), object->y1 + radius * sinf(angle));
    }
    glEnd();


    // Circle outline
    glColor3f(object->sr, object->sg, object->sb);
    glLineWidth(object->swidth);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= segments; i++) {
        float angle = i * angleStep;
        glVertex2f(object->x1 + radius * cosf(angle), object->y1 + radius * sinf(angle));
    }
    glEnd();
}


void drawShape(SHAPE *object) {
	if (object->type == RECTANGLE) {  // rectangle
		drawRectangle(object);

	} else if (object->type == CIRCLE) {  // circle
		drawCircle(object);
	}
}

void drawShapeHighLight(SHAPE *object) {
	if (object->type == RECTANGLE){
	    glColor3f(0.0, 1, 1);
	    glLineWidth(1);
	    glBegin(GL_LINE_LOOP);
	    glVertex2i(object->x1, object->y1);
	    glVertex2i(object->x2, object->y1);
	    glVertex2i(object->x2, object->y2);
	    glVertex2i(object->x1, object->y2);
	    glEnd();
	}
	else
	{
        // Highlight circle
        glColor3f(0.0, 1.0, 1.0);  // Cyan color
        glLineWidth(1);
        int num_segments = 100;  // Number of line segments to approximate the circle
        float cx = object->x1;   // Circle center x
        float cy = object->y1;   // Circle center y
        float radius = sqrt(pow(object->x2 - cx, 2) + pow(object->y2 - cy, 2));  // Radius

        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < num_segments; i++) {
            float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);  // Calculate angle
            float dx = radius * cosf(theta);  // X coordinate
            float dy = radius * sinf(theta);  // Y coordinate
            glVertex2f(cx + dx, cy + dy);     // Add vertex on the circumference
        }
        glEnd();
	}
}

void drawList(LIST *list) {
	NODE *p = list->start;
	while (p) {
		drawShape(p->object);
		p = p->next;
	}
}

void setPixel(GLint x, GLint y) {
	glPointSize(2.0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

// draw points on line of circle
void circlePlotPoints(const GLint& xc, const GLint& yc, const GLint& x,
		const GLint& y) {
// ...
}

// draw circle main function
void circleMidpoint(GLint x1, GLint y1, GLint x2, GLint y2) {
	// ...
}

void circlePlotPointsFill(GLint x1, GLint y1, GLint x, GLint y) {
	// ...
}

void circleMidpointFill(GLint x1, GLint y1, GLint x2, GLint y2) {
	// ...
}
