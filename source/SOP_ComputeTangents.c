#include <GA/GA_Handle.h>
#include <GU/GU_Detail.h>
#include <OP/OP_AutoLockInputs.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <PRM/PRM_Include.h>
#include <UT/UT_DSOVersion.h>
#include "Calculator.h"
#include "SOP_ComputeTangents.h"

static PRM_Name modeName("basic", "Basic Mode");

PRM_Template  SOP_ComputeTangents::myTemplateList[] = {
    PRM_Template(PRM_TOGGLE, 1, &modeName, PRMoneDefaults),
    PRM_Template()
};


OP_Node *SOP_ComputeTangents::myConstructor(OP_Network *net, const char *name, OP_Operator *op)
{
    return new SOP_ComputeTangents(net, name, op);
}

SOP_ComputeTangents::SOP_ComputeTangents(OP_Network *net, const char *name, OP_Operator *op) : SOP_Node(net, name, op)
{
    mySopFlags.setManagesDataIDs(true);
}

SOP_ComputeTangents::~SOP_ComputeTangents()
{
}

OP_ERROR SOP_ComputeTangents::cookMySop(OP_Context &context)
{
    OP_AutoLockInputs inputs(this);
    if (inputs.lock(context) >= UT_ERROR_ABORT)
    {
        return error();
    }
    duplicateSource(0, context);

    // Perform basic checks to avoid segfaults. We won't fix anything here
    // because it is easier to do inside Houdini.
    GA_ROHandleV3 n(gdp, GA_ATTRIB_VERTEX, "N");
    if (n.isInvalid())
    {
        addError(SOP_ERR_INVALID_SRC, "(no vertex normals)");
        return error();
    }

    GA_ROHandleV3 uv(gdp, GA_ATTRIB_VERTEX, "uv");
    if (uv.isInvalid())
    {
        addError(SOP_ERR_INVALID_SRC, "(no vertex uvs)");
        return error();
    }

    for (GA_Iterator i(gdp->getPrimitiveRange()); !i.atEnd(); i.advance())
    {
        GA_Size numvtx = gdp->getPrimitive(*i)->getVertexCount();
        if (numvtx != 3 && numvtx != 4)
        {
            addError(SOP_ERR_INVALID_SRC, "(only quads and triangles allowed)");
            return error();
        }
    }

    bool basic = evalInt("basic", 0, context.getTime());

    if (basic)
    {
        GA_RWHandleV3 tangentuHandle(gdp->addFloatTuple(GA_ATTRIB_VERTEX, "tangentu", 3));
        GA_RWHandleF signHandle(gdp->addFloatTuple(GA_ATTRIB_VERTEX, "sign", 1));
        Calculator().callMorty(gdp, basic);
        tangentuHandle.bumpDataId();
        signHandle.bumpDataId();
    }
    else
    {
        GA_RWHandleV3 tangentuHandle(gdp->addFloatTuple(GA_ATTRIB_VERTEX, "tangentu", 3));
        GA_RWHandleV3 tangentvHandle(gdp->addFloatTuple(GA_ATTRIB_VERTEX, "tangentv", 3));
        GA_RWHandleF maguHandle(gdp->addFloatTuple(GA_ATTRIB_VERTEX, "magu", 1));
        GA_RWHandleF magvHandle(gdp->addFloatTuple(GA_ATTRIB_VERTEX, "magv", 1));
        GA_RWHandleI keepHandle(gdp->addIntTuple(GA_ATTRIB_VERTEX, "keep", 1));
        Calculator().callMorty(gdp, basic);
        tangentuHandle.bumpDataId();
        tangentvHandle.bumpDataId();
        maguHandle.bumpDataId();
        magvHandle.bumpDataId();
        keepHandle.bumpDataId();
    }
    return error();
}

void newSopOperator(OP_OperatorTable *table)
{
    table->addOperator(new OP_Operator("computetangents", "Compute Tangents",
        SOP_ComputeTangents::myConstructor,
        SOP_ComputeTangents::myTemplateList,
        1, 1));
}
