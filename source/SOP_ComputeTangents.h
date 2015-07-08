#ifndef __SOP_ComputeTangents_h__
#define __SOP_ComputeTangents_h__

#include <SOP/SOP_Node.h>

// Compute Tangents SOP
//
// Computes and stores tangents suitable for normal map baking using a robust
// tangent basis calculator written by Morten S. Mikkelsen. All operations
// performing via Calculator class.
class SOP_ComputeTangents : public SOP_Node
{
public:
    SOP_ComputeTangents(OP_Network *net, const char *name, OP_Operator *op);
    static PRM_Template myTemplateList[];
    static OP_Node *myConstructor(OP_Network *net, const char *name, OP_Operator *op);
    virtual ~SOP_ComputeTangents();

protected:
    virtual OP_ERROR cookMySop(OP_Context &context);
};

#endif
