/*
 * Description: implementation of SimpleDraw file functions
 * Author: HBF
 * Version: 2021-08-24
 */

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#include "file.hpp"
#include "object.hpp"

#define MaxNumObj 100
#define GL_BGR_EXT 0x80E0
#define GL_BGR     0x80E0
#define GL_BGRA    0x80E1

extern LIST objlist;

int saveBitmap(const char *ptrcFileName, int nX, int nY, int nWidth, int nHeight) {

  // your implementation
	return 1;
}

int saveSVG(const char *filename, int winWidth, int winHeight) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) return EXIT_FAILURE;

    char line[255];

    // Write header data for SVG
    sprintf(line, "<?xml version=\"1.0\" standalone=\"no\"?>\n");
    fputs(line, fp);
    sprintf(line, "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
    fputs(line, fp);
    sprintf(line, "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
    fputs(line, fp);
    sprintf(line,
            "<svg width=\"%d\" height=\"%d\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n",
            winWidth, winHeight);
    fputs(line, fp);

    // Traverse through the object list and write each shape to the SVG file
    NODE *current = objlist.start; // Start from the beginning of the list

    while (current != NULL) {
        SHAPE *shape = current->object; // Get the shape object

        if (shape->type == RECTANGLE) {
            // Write rectangle data to SVG
            int x1 = shape->x1 < shape->x2 ? shape->x1 : shape->x2;
            int y1 = shape->y1 < shape->y2 ? shape->y1 : shape->y2;
            int width = abs(shape->x2 - shape->x1);
            int height = abs(shape->y2 - shape->y1);

            sprintf(line, "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"none\" stroke=\"rgb(%f,%f,%f)\" stroke-width=\"%d\"/>\n",
                    x1, y1, width, height,
                    shape->sr, shape->sg, shape->sb, shape->swidth);
            fputs(line, fp);
        } else if (shape->type == CIRCLE) {
            // Write circle data to SVG
            int cx = shape->x1; // Circle center x
            int cy = shape->y1; // Circle center y
            int px = shape->x2; // Point on the circle
            int py = shape->y2;

            // Calculate the radius as the distance between (cx, cy) and (px, py)
            float radius = sqrt(pow(px - cx, 2) + pow(py - cy, 2));

            sprintf(line, "<circle cx=\"%d\" cy=\"%d\" r=\"%f\" fill=\"none\" stroke=\"rgb(%f,%f,%f)\" stroke-width=\"%d\"/>\n",
                    cx, cy, radius,
                    shape->sr, shape->sg, shape->sb, shape->swidth);
            fputs(line, fp);
        }

        current = current->next; // Move to the next node
    }

    sprintf(line, "</svg>\n");
    fputs(line, fp);
    fclose(fp);

    return EXIT_SUCCESS;
}

int openSVG(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return EXIT_FAILURE;

    int lineLength = 255;
    char line[lineLength];
    int x1, y1, w, h, fr, fg, fb, sr, sg, sb, sw; // Variables to hold scan values

    // Read line by line, if it is a line of rect/circle element, retrieve the attribute values
    while (fgets(line, lineLength, fp)) {
        SHAPE *shapeObj;

        // Parsing rectangle elements
        if (line[0] == '<' && line[1] == 'r') { // rectangle
            sscanf(line,
                   "<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\" fill=\"rgb(%d,%d,%d)\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"%d\"/>",
                   &x1, &y1, &w, &h, &fr, &fg, &fb, &sr, &sg, &sb, &sw);

            shapeObj = (SHAPE *)malloc(sizeof(SHAPE));
            shapeObj->type = RECTANGLE;
            shapeObj->x1 = x1;
            shapeObj->y1 = y1;
            shapeObj->x2 = x1 + w;
            shapeObj->y2 = y1 + h;
            shapeObj->fr = fr / 255.0;
            shapeObj->fg = fg / 255.0;
            shapeObj->fb = fb / 255.0;
            shapeObj->sr = sr / 255.0;
            shapeObj->sg = sg / 255.0;
            shapeObj->sb = sb / 255.0;
            shapeObj->swidth = sw;
            insert(&objlist, shapeObj);

        } else if (line[0] == '<' && line[1] == 'c') { // circle
            int cx, cy, radius;
            sscanf(line,
                   "<circle cx=\"%d\" cy=\"%d\" r=\"%d\" fill=\"rgb(%d,%d,%d)\" stroke=\"rgb(%d,%d,%d)\" stroke-width=\"%d\"/>",
                   &cx, &cy, &radius, &fr, &fg, &fb, &sr, &sg, &sb, &sw);

            shapeObj = (SHAPE *)malloc(sizeof(SHAPE));
            shapeObj->type = CIRCLE;
            shapeObj->x1 = cx;  // Center X
            shapeObj->y1 = cy;  // Center Y
            shapeObj->x2 = cx + radius; // x2 can be used as a point on the circumference
            shapeObj->y2 = cy + radius; // y2 can be used as a point on the circumference
            shapeObj->fr = fr / 255.0;
            shapeObj->fg = fg / 255.0;
            shapeObj->fb = fb / 255.0;
            shapeObj->sr = sr / 255.0;
            shapeObj->sg = sg / 255.0;
            shapeObj->sb = sb / 255.0;
            shapeObj->swidth = sw;
            insert(&objlist, shapeObj);
        }
    }

    fclose(fp);
    return EXIT_SUCCESS;
}

