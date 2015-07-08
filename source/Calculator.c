#include <GU/GU_Detail.h>
#include "Calculator.h"

// Initialize MikkTSpaceInterface with callbacks and run calculator.
void Calculator::callMorty(GU_Detail *gdp, bool basic)
{
    SMikkTSpaceInterface iface;
    iface.m_getNumFaces = getNumFaces;
    iface.m_getNumVerticesOfFace = getNumVerticesOfFace;
    iface.m_getPosition = getPosition;
    iface.m_getNormal = getNormal;
    iface.m_getTexCoord = getTexCoord;
    iface.m_setTSpaceBasic = basic ? setTSpaceBasic : NULL;
    iface.m_setTSpace = basic ? NULL : setTSpace;

    SMikkTSpaceContext context;
    context.m_pInterface = &iface;
    context.m_pUserData = gdp;

    genTangSpaceDefault(&context);
}

// Return number of primitives in the geometry.
int Calculator::getNumFaces(const SMikkTSpaceContext *context)
{
    // Cast the void pointer from context data to our GU_Detail pointer.
    GU_Detail *gdp = static_cast <GU_Detail *> (context->m_pUserData);
    return gdp->getNumPrimitives();
}

// Return number of vertices in the primitive given by index.
int Calculator::getNumVerticesOfFace(const SMikkTSpaceContext *context,
                                     const int primnum)
{
    GU_Detail *gdp = static_cast <GU_Detail *> (context->m_pUserData);
    return gdp->getPrimitiveByIndex(primnum)->getVertexCount();
}

// Write 3-float position of the vertex's point.
void Calculator::getPosition(const SMikkTSpaceContext *context,
                             float outpos[],
                             const int primnum,
                             const int vtxnum)
{
    GU_Detail *gdp = static_cast <GU_Detail *> (context->m_pUserData);
    // Compute the offset of element using indices.
    GA_Primitive *prim = gdp->getPrimitiveByIndex(primnum);
    GA_Offset ptnum = prim->getPointOffset(vtxnum);

    // Access point position using offset.
    GA_ROHandleV3 handle(gdp->getP());
    UT_Vector3F pos = handle.get(ptnum);

    // Write into the input 3-float array.
    outpos[0] = pos[0];
    outpos[1] = pos[1];
    outpos[2] = pos[2];
}

// Write 3-float vertex normal.
void Calculator::getNormal(const SMikkTSpaceContext *context,
                           float outnormal[],
                           const int primnum,
                           const int vtxnum)
{
    GU_Detail *gdp = static_cast <GU_Detail *> (context->m_pUserData);
    GA_Primitive *prim = gdp->getPrimitiveByIndex(primnum);
    GA_Offset lvtxnum = prim->getVertexOffset(vtxnum);

    GA_ROHandleV3 handle(gdp, GA_ATTRIB_VERTEX, "N");
    UT_Vector3F normal = handle.get(lvtxnum);

    outnormal[0] = normal[0];
    outnormal[1] = normal[1];
    outnormal[2] = normal[2];
}

// Write 2-float vertex uv.
void Calculator::getTexCoord(const SMikkTSpaceContext *context,
                             float outuv[],
                             const int primnum,
                             const int vtxnum)
{
    GU_Detail *gdp = static_cast <GU_Detail *> (context->m_pUserData);
    GA_Primitive *prim = gdp->getPrimitiveByIndex(primnum);
    GA_Offset lvtxnum = prim->getVertexOffset(vtxnum);

    GA_ROHandleV3 handle(gdp, GA_ATTRIB_VERTEX, "uv");
    UT_Vector3F uv = handle.get(lvtxnum);

    outuv[0] = uv[0];
    outuv[1] = uv[1];
}

// Compute and set attributes on the geometry vertex. Basic version.
void Calculator::setTSpaceBasic(const SMikkTSpaceContext *context,
                                const float tangentu[],
                                const float sign,
                                const int primnum,
                                const int vtxnum)
{
    GU_Detail *gdp = static_cast <GU_Detail *> (context->m_pUserData);
    GA_Primitive *prim = gdp->getPrimitiveByIndex(primnum);
    GA_Offset lvtxnum = prim->getVertexOffset(vtxnum);

    GA_RWHandleV3 tangentuHandle(gdp->findFloatTuple(GA_ATTRIB_VERTEX, "tangentu", 3));
    GA_RWHandleF signHandle(gdp->findFloatTuple(GA_ATTRIB_VERTEX, "sign"));

    tangentuHandle.set(lvtxnum, UT_Vector3F(tangentu[0], tangentu[1], tangentu[2]));
    signHandle.set(lvtxnum, sign);
}

// Compute and set attributes on the geometry vertex.
void Calculator::setTSpace(const SMikkTSpaceContext *context,
                           const float tangentu[],
                           const float tangentv[],
                           const float magu,
                           const float magv,
                           const tbool keep,
                           const int primnum,
                           const int vtxnum)
{
    GU_Detail *gdp = static_cast <GU_Detail *> (context->m_pUserData);
    GA_Primitive *prim = gdp->getPrimitiveByIndex(primnum);
    GA_Offset lvtxnum = prim->getVertexOffset(vtxnum);

    GA_RWHandleV3 tangentuHandle(gdp->findFloatTuple(GA_ATTRIB_VERTEX, "tangentu", 3));
    GA_RWHandleV3 tangentvHandle(gdp->findFloatTuple(GA_ATTRIB_VERTEX, "tangentv", 3));
    GA_RWHandleF maguHandle(gdp->findFloatTuple(GA_ATTRIB_VERTEX, "magu"));
    GA_RWHandleF magvHandle(gdp->findFloatTuple(GA_ATTRIB_VERTEX, "magv"));
    GA_RWHandleI keepHandle(gdp->findIntTuple(GA_ATTRIB_VERTEX, "keep"));

    tangentuHandle.set(lvtxnum, UT_Vector3F(tangentu[0], tangentu[1], tangentu[2]));
    tangentvHandle.set(lvtxnum, UT_Vector3F(tangentv[0], tangentv[1], tangentv[2]));
    maguHandle.set(lvtxnum, magu);
    magvHandle.set(lvtxnum, magv);
    keepHandle.set(lvtxnum, keep);
}
