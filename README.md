
# VOIXXX Plugin for OBS Studio

Este plugin pertenece a Grupo CEFI S.A.S y es parte del desarrollo del producto “VOIXXX”. Es un plugin para OBS Studio con autenticación y control de uso.

## Requerimientos Funcionales
- Autenticación obligatoria (dummy: usuario "admin", contraseña "password").
- Subtítulos cada 5 segundos indicando acceso a GPU.
- Control de uso: Funciona 30 segundos gratis, luego requiere upgrade a premium.
- Upgrade dummy: Permite uso indefinido.

## Requerimientos Técnicos
- Compatible con Windows.
- Desarrollado en C++ con Qt y SDK de OBS.

## Instalación y Prueba
1. Instala OBS Studio, Visual Studio 2019+, CMake y Qt5.
2. Descarga el SDK de OBS desde GitHub (obsproject/obs-studio).
3. Clona este repositorio: `git clone https://github.com/tuusuario/voiXXX-plugin.git`
4. Crea carpeta build: `mkdir build && cd build`
5. Configura con CMake: `cmake ..`
6. Compila: `cmake --build . --config Release`
7. Copia el .dll a `C:\Program Files\obs-studio\obs-plugins\64bit\`.
8. Reinicia OBS y prueba: Crea una fuente de texto "VOIXXX_Subtitle".

## Dependencias
- OBS Studio
- Qt5
- CMake
- Visual Studio

## Entrega
powered by DALATRAX
