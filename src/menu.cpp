/*
 * Description: implementation of menu.hpp
 * Author: HBF
 * Version: 2021-08-24
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include "menu.hpp"
#include "object.hpp"
#include "edit.hpp"
#include "file.hpp"

extern LIST objlist;
extern GLsizei winHeight, winWidth;
extern GLint oprMode, isInMenu, objType, isInMove;
extern NODE *selectNode;
extern GLint strokeWidth;
extern GLfloat fillred, fillgreen, fillblue, sred, sgreen, sblue;

void addMenu() {

	GLint drawMenuID, styleMenuID, fillColorMenuFcnID, strokefillColorMenuFcnID,
			strokeWidthMenuID, editMenuFcnID, fileMenuFcnID;

	drawMenuID = glutCreateMenu(drawMenuFcn);
	glutAddMenuEntry("Rectangle", 1);
	glutAddMenuEntry("Circle", 2);

	fillColorMenuFcnID = glutCreateMenu(fillColorMenuFcn);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Black", 4);
	glutAddMenuEntry("White", 5);

	strokefillColorMenuFcnID = glutCreateMenu(strokeColorMenuFcn);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Black", 4);
	glutAddMenuEntry("White", 5);

	strokeWidthMenuID = glutCreateMenu(strokeWidthMenuFcn);
	glutAddMenuEntry("1", 1);
	glutAddMenuEntry("2", 2);
	glutAddMenuEntry("3", 3);
	glutAddMenuEntry("4", 4);
	glutAddMenuEntry("5", 5);

	styleMenuID = glutCreateMenu(styleSubMenu);
	glutAddSubMenu("Fill Color", fillColorMenuFcnID);
	glutAddSubMenu("Stroke Color", strokefillColorMenuFcnID);
	glutAddSubMenu("Stroke Width", strokeWidthMenuID);

	editMenuFcnID = glutCreateMenu(editMenuFcn);
	glutAddMenuEntry("Select", 1);
	glutAddMenuEntry("Delete", 2);
	glutAddMenuEntry("Move front", 3);
	glutAddMenuEntry("Move back", 4);
	glutAddMenuEntry("Move around", 5);

	fileMenuFcnID = glutCreateMenu(fileMenuFcn);
	glutAddMenuEntry("Save SVG", 1);
	glutAddMenuEntry("Open SVG", 2);
	glutAddMenuEntry("Export Bitmap", 3);

	glutCreateMenu(mainMenuFcn); // Create main pop-up menu.
	glutAddMenuEntry("New", 1);
	glutAddSubMenu("Draw", drawMenuID);
	glutAddSubMenu("Style", styleMenuID);
	glutAddSubMenu("Edit", editMenuFcnID);
	glutAddSubMenu("File", fileMenuFcnID);
	glutAddMenuEntry("Quit", 2);
}

void clear() {
// ...
}

void mainMenuFcn(GLint menuOption) {
	isInMenu = 1;
	switch (menuOption) {
	case 1:
		clear();
		break;
	case 2:
		exit(0);
	}
	isInMenu = 0;
	glutPostRedisplay();
}

void drawMenuFcn(GLint typeOption) {
	oprMode = 0;
	isInMove = 0;
	switch (typeOption) {
	case 1:
		objType = RECTANGLE;
		break;
	case 2:
		objType = CIRCLE;
		break;

	default:
		objType = RECTANGLE;
	}
}

void fileMenuFcn(GLint fileOption) {
// ..
}

void editMenuFcn(GLint editOption) {
	oprMode = 1;
	isInMove = 0;
	switch (editOption){
	case 1:
		editOption = 1;
		break;
	case 2:
		editOption = 2;
		Delete(&selectNode);
		break;
	case 3:
		editOption = 3;
		moveBack(selectNode);
		break;
	case 4:
		editOption = 4;
		moveFront(selectNode);
		break;
	case 5:
		editOption = 5;
		isInMove = 1;
		break;
	}
	glutPostRedisplay();
}

void styleSubMenu(GLint styleOption) {
}

void fillColorMenuFcn(GLint colorOption) {
	switch (colorOption) {
	case 1:
		fillred = 1.0;
		fillgreen = 0.0;
		fillblue = 0.0;
		break;
	case 2:
		fillred = 0.0;
		fillgreen = 1.0;
		fillblue = 0.0;
		break;
	case 3:
		fillred = 0.0;
		fillgreen = 0.0;
		fillblue = 1.0;
		break;
	case 4:
		fillred = 0.0;
		fillgreen = 0.0;
		fillblue = 0.0;
		break;
	case 5:
		fillred = 1.0;
		fillgreen = 1.0;
		fillblue = 1.0;
		break;
	}
}

void strokeColorMenuFcn(GLint colorOption) {
	switch (colorOption) {
	case 1:
		sred = 1.0;
		sgreen = 0.0;
		sblue = 0.0;
		break;
	case 2:
		sred = 0.0;
		sgreen = 1.0;
		sblue = 0.0;
		break;
	case 3:
		sred = 0.0;
		sgreen = 0.0;
		sblue = 1.0;
		break;
	case 4:
		sred = 0.0;
		sgreen = 0.0;
		sblue = 0.0;
		break;
	case 5:
		sred = 1.0;
		sgreen = 1.0;
		sblue = 1.0;
		break;
	}
}

void strokeWidthMenuFcn(GLint width) {
	switch (width){
	case 1:
		strokeWidth = 1;
		break;
	case 2:
		strokeWidth = 2;
		break;
	case 3:
		strokeWidth = 3;
		break;
	case 4:
		strokeWidth = 4;
		break;
	case 5:
		strokeWidth = 5;
		break;
	}
}

