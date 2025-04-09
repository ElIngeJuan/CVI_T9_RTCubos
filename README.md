# Ray Tracing

En esta versión, el enfoque ha sido adaptado para renderizar cubos en lugar de esferas.

🛠️ El código fuente se encuentra en la siguiente carpeta:

| Resultado       | 
|----------------|
| `InOneWeekend` |
| ![download (1)](https://github.com/user-attachments/assets/b67026e3-20fc-4972-ab5a-db7cb319c19f)|

---

## Cómo compilar y ejecutar

Este proyecto usa **CMake** para compilar.

### 🔧 Compilación en Linux/macOS

```bash
cmake -B build/Release -DCMAKE_BUILD_TYPE=Release
cmake --build build/Release
```

### 🔧 Compilación en Windows (CMD o PowerShell)

```bash
cmake -B build
cmake --build build --config Release
```

### ▶️ Ejecutar el programa

Después de compilar, puedes correr el ejecutable así:

```bash
./build/Release/inOneWeekend > image.ppm
```

Esto generará una imagen en formato `.ppm`. Puedes visualizarla con herramientas como [ImageMagick](https://imagemagick.org/):

```bash
magick image.ppm image.png
```

---

## Recursos

- 📘 [Ray Tracing in One Weekend (Web)](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
- 📘 [Ray Tracing: The Next Week (Web)](https://raytracing.github.io/books/RayTracingTheNextWeek.html)
- 📘 [Ray Tracing: The Rest of Your Life (Web)](https://raytracing.github.io/books/RayTracingTheRestOfYourLife.html)
- 🌐 [Repositorio original en GitHub](https://github.com/RayTracing/raytracing.github.io/)
- 🖼️ [ImageMagick para visualizar `.ppm`](https://imagemagick.org/)

---

