### Compute Tangents SOP

Houdini plug-in for tangent basis calculation. Internally uses the mikktspace
library written by Morten S. Mikkelsen. See
[the link](http://wiki.blender.org/index.php/Dev:Shading/Tangent_Space_Normal_Maps)
for further information.

#### Installation

[`SOP_ComputeTangents.dll`](https://github.com/teared/mikktspace-for-houdini/raw/master/SOP_ComputeTangents.dll)
for Windows users. Drop into a `dso` folder inside usual houdini catalog like
`$HIP/dso` or `$HOME/dso`. I've never run a non-Windows PC. [Compiling from source](http://www.sidefx.com/docs/hdk14.0/_h_d_k__intro__compiling.html) is a
sole option for experienced non-Windows users at this moment.

#### Usage
This is not a ready-to-use solution for baking normal maps, only for
[calculating tangents](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/source/mikktspace.c) and auxiliary attributes. Resulting tangents
may appear similar to PolyFrame-generated attribute where `Texture UV
gradient` option was chosen. This tangents can be used to get quality
xNormal-like bakes in Houdini. The shame is Mantra still has no decent
raytrace baking built in.

#### License
This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
