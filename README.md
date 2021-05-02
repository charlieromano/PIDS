 <img src="Pics/UBA.png" height=100>       <img src="Pics/fiuba_logo.jpg" height=50>        <img src="Pics/trenesArgentinos_logo.png" height=50>                                    



# PIDS

Repo limpio para el proyecto PIDS de la CESE 2020

[TOC]



## Iniciar Repositorio

Para ejecutar el software desarrollado en este repositorio hace falta incluir submódulos y también software adicional relacionado a la plataforma EDU-CIAA. Para esto, se explican los pasos:

1. Clonar este repositorio
2. Incluir submódulos
3. Instalar software

### 1: Clonar este repositorio

```bash
git clone https://github.com/charlieromano/PIDS.git
```

### 2: Incluir submódulos

```bash
cd PIDS
git submodule add https://github.com/epernia/firmware_v3.git    #Agrega firmware_v3 como submodulo
```

### 3: Instalar software

Debe descargar de [releases](https://github.com/epernia/software/releases/tag/r1.1.0) la versión para Windows o Linux.

Link: https://github.com/epernia/software/releases/tag/r1.1.0

Descomprimir la carpeta en una ruta conocida, sin espacios y con los permisos adecuados. Se recomiendan:

- **Windows**. C:\CIAA\
- **Linux**. $HOME/CIAA/

Luego ingresar a la carpeta y ejecutar el lanzador de apliaciones. 

## Crear un programa

Ir al directorio del repositorio, y luego desde el submodule firmware_v3 crear un program folder:

```bash
cd PIDS
cd firmware_v3          #Entras al repo del firmware_v3
make new_program        #Ejecutas el script para crear nuevo programa
```

Se debe abrir un cuadro de diálogo como el siguiente:

<img src='Pics/make_create.jpeg'  height="300">

Luego se puede chequear el árbol del proyecto:

<img src='Pics/tree_repo.jpeg' height=300>