#Generacion de discos para la calificacion de la segunda fase FAVOR VERIFICAR QUE NO REALIZA Y COMENTAR LOS COMANDOS
#GRACIAS Y EXITOS EN SU CALIFICACIÓN... 
MKdisk -sizE=120 -unit=M -path="/home/archivos/fase2/D1.disk" -fit=FF




fdisk -path="/home/archivos/fase2/D1.disk" -sizE=10    -UniT=M  -type=P -fit=FF -name="PRI1"
fdisk -path="/home/archivos/fase2/D1.disk" -sizE=10000                  -fit=BF -name="PRI2"
fdisk -path="/home/archivos/fase2/D1.disk" -sizE=10    -unit=M                  -name="PRI3"

#Debería generar los ids: vda1, vdb1, vda2, vdb2, vda3, vdb3
#vda para el D2.disk y vdb para d1.disk
mouNt -NamE="PRI1"  -path="/home/archivos/fase2/D1.disk"
mouNt -NamE="PRI2"  -path="/home/archivos/fase2/D1.disk"
mouNt -NamE="PRI3"  -path="/home/archivos/fase2/D1.disk"


#Crea el sistema de archivos EXT3 en todas las particiones primarias PRI1 
mkfs -id=vda1 -type=Full 


#nos logueamos en la particion PRI1 con nuestro usuario root, cambiar pwd a su no.carne
loGin -usr=root -pwd=123 -id=vda1

#Crearemos un grupo llamado "MySql" ,"Oracle" y "DB2"
mkgrp -name="MySql"
mkgrp -name="Oracle"
mkgrp -name="DB2"

#Crearemos 3 usuarios llamados user1, user2 y user3
Mkusr -usr="user1" -grp=MySql -pwd=user1
Mkusr -usr="user2" -grp=Oracle -pwd=user2
Mkusr -usr="user3" -grp=MySql -pwd=user3


logouT

loGin -usr=user1 -pwd=user1 -id=vda1

cat -file=/users.txt

#Crearemos la ruta y las padres que no existan
mkdir -path="/home/archivos/mia/fase2" -p
mkdir -path="/home/archivos/mia/carpeta2" -p
mkdir -path="/home/archivos/mia/carpeta2/a1"
mkdir -path="/home/archivos/mia/carpeta2/a2"
mkdir -path="/home/archivos/mia/carpeta2/a3"
mkdir -path="/home/archivos/mia/carpeta2/a4"
mkdir -path="/home/archivos/mia/carpeta2/a5"
mkdir -path="/home/archivos/mia/carpeta2/a6"
mkdir -path="/home/archivos/mia/carpeta2/a7"
mkdir -path="/home/archivos/mia/carpeta2/a8"
mkdir -path="/home/archivos/mia/carpeta2/a9"
mkdir -path="/home/archivos/mia/carpeta2/a10"

logouT
loGin -usr=user2 -pwd=user2 -id=vda1

mkFile -PatH="/home/archivos/mia/fase2/nerf/unos.txt"       -SIZE=1 -p
mkfile -path="/home/archivos/mia/fase2/archivito/doses.txt" -SIZE=1 -p

mkfile -path="/home/tres.txt"        -SIZE=15 -p
mkfile -path="/home/cuad/cuatro.txt" -SIZE=25 -p


edit -path="/home/archivos/mia/fase2/nerf/unos.txt" -cont ="UNO_UNO_UNO_UNO_UNO_UNO_UNO_UNO_UNO_UNO_UNO_UNO"
edit -path="/home/archivos/mia/fase2/archivito/doses.txt" -cont ="DOS_DOS_DOS_DOS_DOS_DOS_DOS_DOS_DOS_DOS_DOS_DOS"

#vamos a ver el archivo user.txt en el reporte tree
rep -name=tree -Path="/home/wrm/Tree.jpg" -id=vda1

syncronice -id=vda1

pause



