## Compute Tangents SOP

Houdini plug-in bringing [mikktspace] library written by Morten S. Mikkelsen.
Computed tangents can be used to bake normal maps. Resulting normal maps will
be synced with xNormal, Blender, 3D Coat, Unreal Engine 4, Unity and other
software using this library, and may not be synced with Houdini native tangents
well.

[mikktspace]: http://wiki.blender.org/index.php/Dev:Shading/Tangent_Space_Normal_Maps


### Houdini 16 Note
Since Houdini 16.0.514, MikkTSpace supported at render-time via [`vm_bake_usemikkt`](http://www.sidefx.com/docs/houdini/props/mantra#vm_bake_usemikkt)
property. Try it at first, if you don't need Mikk's tangents in SOP level as
geometry attributes.


### Installation
See [Releases](https://github.com/teared/mikktspace-for-houdini/releases) for
Windows binaries.

To compile on Windows with Visual Studio or Build Tools, [update] `HDK_*` macros
inside `.props` file with your Houdini version and build `.sln` file.

To compile on other operation systems, follow [tutorial] on HDK building and
use source code files directly.

[update]: https://github.com/teared/mikktspace-for-houdini/commit/6a9a7518e4e08735da99bb0808a3dfb3a2a12db9#diff-c3420d76b2c2d06ac74397cb0b7d9374
[tutorial]: http://www.sidefx.com/docs/hdk15.0/_h_d_k__intro__compiling.html


#### License
Public domain.
