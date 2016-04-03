## Compute Tangents SOP
Houdini plug-in bringing mikktspace library written by Morten S. Mikkelsen.
Computed tangents can be used to bake normal maps. Resulting normal maps will
be synced with xNormal, Blender, 3D Coat, Unreal Engine 4, Unity and other
software included this library, and may not be synced well with the Houdini.
[More info](http://wiki.blender.org/index.php/Dev:Shading/Tangent_Space_Normal_Maps).

tl;dr:
   [Used](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_pig_mikk.png) /
   [Unused](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_pig_mantra.png)

#### Installation
   [`SOP_ComputeTangents.dll`](https://github.com/teared/mikktspace-for-houdini/raw/master/SOP_ComputeTangents.dll)

Build for Windows only. Linux users need to [compile] it from source. Drop compiled binary into a `dso` folder inside usual houdini catalog like `$HIP/dso` or `$HOME/dso`.

[compile]: http://www.sidefx.com/docs/hdk15.0/_h_d_k__intro__compiling.html

#### Usage
   [`bake.hipnc`](https://github.com/teared/mikktspace-for-houdini/raw/master/extras/bake.hipnc)

Triangulate unwrapped mesh, compute soft vertex normals. Compute tangents.
Trace object normal from highpoly and multiply it by inverse of matrix3 built
from `tangentu`, `tangentv` and `normal` components. To bake with hard edges,
store two sets of soft and hard-edged normals in different attributes. Use
soft normal as a tracing direction inside shader and hardened normal as a
normal component of tangent basis.


##### Houdini 15 Note

Micropolygon baking workflow no longer works. Resulting normal maps will
differ from xNormal bakes. They will, however, be synced and look good. You
also get all features of the Bake Texture ROP. Notable artifacts produced by
Mantra are "torn edges" on UV seams. They may be very visible, and may be not,
depending on situation.
   [MikkTSpace](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/tornedges_mikk.png) vs
   [Mantra](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/tornedges_mantra.png);
   [MikkTSpace](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/tornedges_mikk2.png) vs
   [Mantra](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/tornedges_mantra2.png).

Before trying MikkTSpace plugin, give Mantra a chance. Calculators are
different, but algorithms may be (mostly) the same, because resulting tangents
are nearly similar. It means that normal maps baked with default tangents are
already synced with MikkTSpace apps quite well, a wa-a-ay better than some other
apps with their own calculators.

   [MikkTSpace](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/view_mikk.png),
   [Mantra](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/view_mantra.png),
   [xNormal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/view_xnormal.png),
   [Unsynced](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/view_unsynced.png) (realistic fake).


##### Tests

1. Triangulated, soft normals. Consider as default setup.
Cases:
   [MikkTSpace](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/case_tris_soft_mikk.png),
   [Mantra](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/case_tris_soft_mantra.png),
   [xNormal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/case_tris_soft_xnormal.png),
   [Inside Unreal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/case_nstyle_tris_soft_mikk);
Pigs:
   [MikkTSpace](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/pig_tris_soft_mikk.png),
   [Mantra](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/pig_tris_soft_mantra.png),
   [xNormal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/pig_tris_soft_xnormal.png),
   [Inside Unreal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/pig_nstyle_tris_soft_mikk).
Spot some tearing at UV seams in Mantra examples.

2. Triangulated, soft normals with attribute smoothing. 
Cases:
   [MikkTSpace](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/case_tris_soft_smoothed_mikk.png),
   [Mantra](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/case_tris_soft_smoothed_mantra.png),
   [xNormal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/case_tris_soft_smoothed_xnormal.png),
   [Inside Unreal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/case_nstyle_tris_soft_smoothed_mikk.png);
Pigs:
   [MikkTSpace](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/pig_tris_soft_smoothed_mikk.png),
   [Mantra](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/pig_tris_soft_smoothed_mantra.png),
   [xNormal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/pig_tris_soft_smoothed_xnormal.png),
   [Inside Unreal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/pig_nstyle_tris_soft_smoothed_mikk.png).

3. Quad mesh, soft normals with attribute smoothing.
Cases:
   [MikkTSpace](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/case_quads_soft_smoothed_mikk.png),
   [Mantra](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/case_quads_soft_smoothed_mantra.png),
   [xNormal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/case_quads_soft_smoothed_xnormal.png),
   [Inside Unreal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/case_nstyle_quads_soft_smoothed_mikk);
Pigs:
   [MikkTSpace](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/pig_quads_soft_smoothed_mikk.png),
   [Mantra](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/pig_quads_soft_smoothed_mantra.png),
   [xNormal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/pig_quads_soft_smoothed_xnormal.png),
   [Inside Unreal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/pig_nstyle_quads_soft_smoothed_mikk);
Examples of automatic triangulation:
   [Houdini](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/triangulation_houdini.png),
   [UE4](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/triangulation_ue4.png).

Different normal styles affect tracing directions. Normal maps are quite
different, but there is barely any difference in final shaders in UE4. xNormal
best at dealing with quads, making perfectly synced normal maps, while both
Houdini solutions are slightly unsynced. Before baking in Houdini, geometry
should be triangulated by Divide SOP using Avoid small angles option.


##### More UE4 Tests
Ignore artifacts at pig's ear and at the corner of the mouth, caused by cheating
on retopo. Also ignore jagged highlights on case's highpoly. Visualization shows
world space normals.

Case:
   [Highpoly](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_case_highpoly.png),
   [MikkTSpace](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_case_mikk.png),
   [Mantra](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_case_mantra.png),
   [xNormal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_case_xnormal.png).
Case Viz:
   [Highpoly](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_visualization_case_highpoly.png),
   [MikkTSpace](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_visualization_case_mikk.png),
   [Mantra](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_visualization_case_mantra.png),
   [xNormal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_visualization_case_xnormal.png).

Pig:
   [Highpoly](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_pig_highpoly.png),
   [MikkTSpace](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_pig_mikk.png),
   [Mantra](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_pig_mantra.png),
   [xNormal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_pig_xnormal.png).
Pig Viz:
   [Highpoly](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_visualization_pig_highpoly.png),
   [MikkTSpace](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_visualization_pig_mikk.png),
   [Mantra](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_visualization_pig_mantra.png),
   [xNormal](https://raw.githubusercontent.com/teared/mikktspace-for-houdini/master/extras/images/ue4_visualization_pig_xnormal.png).


#### License
Public domain.