## Compute Tangents SOP

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
xNormal-like bakes in Houdini.

#### Tangent Space Normals Baking
[`bake_normals_example.hdanc`](https://github.com/teared/mikktspace-for-houdini/raw/master/bake_normals_example.hdanc)

Results: [Mantra](http://i.imgur.com/AGGCM7S.png), [xNormal](http://i.imgur.com/ogKP7bL.png).

Sample object space normals, then multiply resulting vector by inversion of
tangent basis, then remap it to 0-1 texture range, then dilate image
[in a proper way](http://wiki.polycount.com/wiki/Edge_padding).
The sampler is very simple, to achieve better results it may be worth to build
something more complex.
