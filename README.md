## Compute Tangents SOP

Houdini plug-in bringing [mikktspace] library written by Morten S. Mikkelsen.
Computed tangents can be used to bake normal maps. Resulting normal maps will
be synced with xNormal, Blender, 3D Coat, Unreal Engine 4, Unity and other
software using this library, and may not be synced well with Houdini.

[mikktspace]: http://wiki.blender.org/index.php/Dev:Shading/Tangent_Space_Normal_Maps

tl;dr:
   [Used](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_pig_mikk.png) /
   [Unused](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_pig_mantra.png) /
   [xNormal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_pig_xnormal.png).



#### Installation
   [`SOP_ComputeTangents.dll`](https://github.com/teared/mikktspace-for-houdini/raw/master/SOP_ComputeTangents.dll)

Build for Windows only. Linux users need to [compile] it from source. Drop
compiled binary into a `dso` folder inside usual houdini catalog like
`$HIP/dso` or `$HOME/dso`.

[compile]: http://www.sidefx.com/docs/hdk15.0/_h_d_k__intro__compiling.html



#### Usage
   [`bake.hipnc`](https://github.com/teared/mikktspace-for-houdini/raw/master/extras/bake.hipnc)

> Houdini 15 Note:

> Micropolygon workflow no longer works. Resulting normal maps will differ
> from xNormal bakes. They will, however, be synced. Before trying MikkTSpace
> plugin, give Mantra a chance. Resulting tangents are nearly similar. Normal
> maps baked with default tangents are already synced with MikkTSpace apps
> quite well, much better than some other apps with their own calculators.
> Notable artifacts produced by default calculator are "[torn edges]" on UV
> seams. Depending on situation, they may be barely visible or even invisible.


[torn edges]: https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/torn_edges.png

Unwrap, triangulate, compute soft vertex normals. Add Compute Tangents SOP.
Optionally, for hard edge bakes using a custom cage: add a cage with same
topology (could be a copied model with averaged normals) and copy it's `P` and
`N` into `rayorigin` and `raydir` attributes on the main model. By default, if
no cage present, main geometry's `P` and `N` will be used to trace normals.

Don't use Bake Shader SHOP. Instead, create a custom shader based on
`/vex/trace_normals`. Trace object normal from highpoly and multiply it by
inverse of orthonormalized matrix3 built from `tangentu`, `tangentv` and
`normal` components. To render use Bake Texture ROP. Set `minmax edge` as
pixel filter to disable edge antialiasing, leave highpoly geometry string
blank, otherwise it will be hidden by render script intended for default
workflow.



##### Bake Tests
|           |                  |              |               |
|-----------|------------------|--------------|---------------|
| Case Bake | [MikkTSpace][c1] | [Mantra][c2] | [xNormal][c3] |
| Case UE4  | [MikkTSpace][c4] | [Mantra][c5] | [xNormal][c6] |
| Pig Bake  | [MikkTSpace][p1] | [Mantra][p2] | [xNormal][p3] |
| Pig UE4   | [MikkTSpace][p4] | [Mantra][p5] | [xNormal][p6] |

[c1]: https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/case_soft_mikk.png
[c2]: https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/case_soft_mantra.png
[c3]: https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/case_soft_xnormal.png
[c4]: https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_case_mikk.png
[c5]: https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_case_mantra.png
[c6]: https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_case_xnormal.png
[p1]: https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/pig_soft_mikk.png
[p2]: https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/pig_soft_mantra.png
[p3]: https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/pig_soft_xnormal.png
[p4]: https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_pig_mikk.png
[p5]: https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_pig_mantra.png
[p6]: https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_pig_xnormal.png

Test models: a "case", an abstract hard-surface geo exposing unsynced bake
errors; a pig head, an organic model coming with Houdini installation. xNormal
here chosen as well-tested and trusted baker used by many artists. Spot some
tangents discontinuities at UV seams in Mantra bakes.



#### License
Public domain.
