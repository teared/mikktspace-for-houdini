## Compute Tangents SOP

Houdini plug-in for tangent basis calculation. Internally uses the mikktspace
library written by Morten S. Mikkelsen. See
[the link](http://wiki.blender.org/index.php/Dev:Shading/Tangent_Space_Normal_Maps)
for further information.

#### Installation

[`SOP_ComputeTangents.dll`](https://github.com/teared/mikktspace-for-houdini/raw/master/SOP_ComputeTangents.dll)
for Windows users. Drop into a `dso` folder inside usual houdini catalog like
`$HIP/dso` or `$HOME/dso`. I've never run a non-Windows PC.
[Compiling from source](http://www.sidefx.com/docs/hdk14.0/_h_d_k__intro__compiling.html)
is a sole option for experienced non-Windows users at this moment.

#### Usage
Results: [Mantra](http://i.imgur.com/AGGCM7S.png), [xNormal](http://i.imgur.com/ogKP7bL.png).

This is not a ready-to-use solution for baking normal maps, only for
[calculating tangents](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/source/mikktspace.c)
and auxiliary attributes. Resulting tangents may appear similar to PolyFrame's
attributes where `Texture UV gradient` option was chosen. This tangents can be
used to get xNormal-like bakes in Houdini. Resulting normals will be synced
with Blender, xNormal, Unreal Engine 4, Unity, Substances, Quixel Suite and
other applications using this library, and may not be synced well with Houdini
itself.

The plugin was compiled for new Houdini 15 version. Just render in
Micropolygon with standard Mantra ROP node, by adding back `UV Render Object`
and related properties. They can be found in help for Houdini 14. However,
still not tested it myself yet.

#### Houdini 15 Note

This note thoroughly being updated while I figuring things up.

New tools made it extremely non-trivial to bake Normal Map appear similar to
xNormal. The Mikk's tangents still there, but the way Mantra uses lens shader
still produces a lot of shading artifacts on texture's seams, even for
Houdini's native tangents. To force Mantra use custom bake shader comment out
`$HH/python2.7libs/baketextureutil.py`'s exception:

    if uvobjectsop.geometry().findPrimAttrib('shop_materialpath'):
        # raise hou.OperationFailed('UV object \''+uvobjectnode.path()+'\' has \'shop_materi...
        pass

You should override this script by creating same structure with $HIP or any
user catalog instead of $HH. Then you need create custom lens shader and
override it too. The code appears to be simple, maybe getting rid of
uvunwrap() function call will work.
