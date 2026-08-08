Although the physics and rendering equations of this raytracer follows that of [Shirley](https://github.com/petershirley)/[Black](https://github.com/trevordblack)/[Hollasch](https://github.com/hollasch)'s Ray Tracing series ([RTIOW](https://raytracing.github.io/books/RayTracingInOneWeekend.html), [RT:TNW](https://raytracing.github.io/books/RayTracingTheNextWeek.html)), but the architecture and design decisions do not.  
And they need explanations, which is the intent of this document to clear the choices as well as some of implementation details.  

The major design decisions made are:  

1. A Raytracer should ultimately be able to easily accept different geometries. In other words, it should be fairly easy for the *user* of a raytracer library to add new **Types**.  
2. On the other hand, the case for introducing a new Material is the opposite of above. There are a fixed set of materials that the raytracer *knows* how to handle and they have an implementation. To add a new Type of material, it is necessary to make changes to the internals of the library. But adding new Operations should be simple and straightforward. Putting it differently, it should be possible to easily add new **Operations** for (a fixed set of) different types of material.  

With these design decisions in mind, Sharlune Raytracer implements:  
1) **Type Erasure Pattern** for any **_'Hittable'_** object (see `./include/hittable.h`), enables us to easily add a new type of geometry (see `./include/basic_geometries.h`) without changing any other class. Additionally utilizing **Strategy Design Pattern**, it is similarly simple to add a ray-intersection strategy for the new geometry (see `./include/hit_strategies.h`).  
2) **Visitor Pattern** for the supported materials, utilizing C++17's `std::variant` and `std::visit` to get a value-based, non-intrusive implementation (see `material.h`, `scatter.h` for the scattering visitor, and e.g. `PinholeCamera::ray_color` implementation for the actual visiting).  

--- 
Next noteworthy decision, is the heavily templated, `./include/vectormath.h` which follows **CRTP Pattern** as an implementation pattern with various necessary **_skills_**. This way it is both flexible to keep common operations between different tuples, but also to give only the necessary skills to the proper tuple.  
For example, in a raytracer, only 2d, 3d and 4d tuples are needed and this design easily enforces that. Furthermore, and perhaps more interesting, although all three of Point, Vector and Color are tuples, but only 3d vectors can have meaningful cross product in our context, which is as easy as setting that skill for the Vec3 and not for any other type.  

