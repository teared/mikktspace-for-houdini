#ifndef __Calculator_h__
#define __Calculator_h__

#include "mikktspace.h"

class Calculator
{
public:
    // Initialize MikkTSpaceInterface with callbacks and run calculator.
    void callMorty(GU_Detail * gdp, bool basic = true);

    // Return number of primitives in the geometry.
    static int  getNumFaces(const SMikkTSpaceContext *context);

    // Return number of vertices in the primitive given by index.
    static int  getNumVerticesOfFace(const SMikkTSpaceContext *context, const int primnum);

    // Write 3-float position of the vertex's point.
    static void getPosition(const SMikkTSpaceContext *context, float pos[],  const int primnum, const int vtxnum);

    // Write 3-float vertex normal.
    static void getNormal(const SMikkTSpaceContext *context, float normal[], const int primnum, const int vtxnum);

    // Write 2-float vertex uv.
    static void getTexCoord(const SMikkTSpaceContext *context, float uv[], const int primnum, const int vtxnum);

    // Compute and set attributes on the geometry vertex.
    static void setTSpaceBasic(const SMikkTSpaceContext *context, const float tangentu[], const float sign, const int primnum, const int vtxnum);
    static void setTSpace(const SMikkTSpaceContext *context, const float tangentu[], const float tangentv[], const float magu, const float magv, const tbool keep, const int primnum, const int vtxnum);
};

#endif
