/*
 * Description: implementation of edit.hpp
 * Author: HBF
 * Version: 2021-08-24
 */

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "object.hpp"

extern LIST objlist;

GLint min(GLint x, GLint y) {
	return x < y ? x : y;
}

GLint max(GLint x, GLint y) {
	if (x < y)
		return y;
	else
		return x;
}

NODE *select(GLint x, GLint y) {
    NODE *current = objlist.end;  // Start from the end of the list (top-most shape)
    NODE *selectedNode = NULL;    // Variable to hold the currently selected node
    int objectNumber = 1;         // Counter for the object number

    while (current != NULL) {
        if (current->object->type == RECTANGLE) {
            // Handle rectangle selection
            int x1 = current->object->x1;
            int y1 = current->object->y1;
            int x2 = current->object->x2;
            int y2 = current->object->y2;

            // Determine the actual bounds of the rectangle, accounting for any orientation
            int minX = (x1 < x2) ? x1 : x2;
            int maxX = (x1 > x2) ? x1 : x2;
            int minY = (y1 < y2) ? y1 : y2;
            int maxY = (y1 > y2) ? y1 : y2;

            // Check if (x, y) lies within the rectangle
            if (x >= minX && x <= maxX && y >= minY && y <= maxY) {
                printf("Selected Rectangle Number: %d\n", objectNumber);
                return current; // Return immediately on finding a match
            }
        } else if (current->object->type == CIRCLE) {
            // Handle circle selection
            int cx = current->object->x1;  // Circle center x
            int cy = current->object->y1;  // Circle center y
            int px = current->object->x2;  // Point on the circle
            int py = current->object->y2;

            // Calculate the radius as the distance between (cx, cy) and (px, py)
            float radius = sqrt(pow(px - cx, 2) + pow(py - cy, 2));

            // Calculate the distance between (cx, cy) and (x, y)
            float distance = sqrt(pow(x - cx, 2) + pow(y - cy, 2));

            // Check if the distance is less than or equal to the radius
            if (distance <= radius) {
                printf("Selected Circle Number: %d\n", objectNumber);
                return current; // Return immediately on finding a match
            }
        }

        // Move to the previous node (closer to the background)
        current = current->prev;
        objectNumber++;
    }

    // No shape contains the point
    return NULL;
}

void Delete(NODE **pp) {
	deleteNode(&objlist, pp);
}

void moveFront(NODE *p) {
    // Check if the node is NULL or already at the start of the list
    if (p == NULL || p == objlist.start) {
        return; // No need to move if it's already at the start or the node is NULL
    }

    // If the node is the only node in the list, no need to move
    if (objlist.start == objlist.end) {
        return; // Only one node in the list
    }

    // If the node is the last node, update the end pointer
    if (p == objlist.end) {
        objlist.end = p->prev;
        objlist.end->next = NULL;
    }
    // Otherwise, adjust the neighboring nodes' pointers
    else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }

    // Move the node to the start
    p->next = objlist.start;
    p->prev = NULL;

    objlist.start->prev = p;  // Link the first node to the selected node
    objlist.start = p;        // Update the start pointer to the selected node

}

void moveBack(NODE *p) {
	// Check if the node is NULL or already at the end of the list
	    if (p == NULL || p == objlist.end) {
	    	printf("Already at the start");
	        return; // No need to move if it's already at the end or the node is NULL
	    }

	    // If the node is the only node in the list, no need to move
	    if (objlist.start == objlist.end) {
	        return; // Only one node in the list
	    }

	    // If the node is the first node, update the start pointer
	    if (p == objlist.start) {
	        objlist.start = p->next;
	        objlist.start->prev = NULL;
	    }
	    // Otherwise, adjust the neighboring nodes' pointers
	    else {
	        p->prev->next = p->next;
	        p->next->prev = p->prev;
	    }

	    // Move the node to the end
	    p->prev = objlist.end;
	    p->next = NULL;

	    objlist.end->next = p;  // Link the last node to the selected node
	    objlist.end = p;        // Update the end pointer to the selected node
}

