
#Generacion de discos para la calificacion de la segunda fase FAVOR VERIFICAR QUE NO REALIZA Y COMENTAR LOS COMANDOS
#GRACIAS Y EXITOS EN SU CALIFICACIÓN... 
MKdisk -sizE=120 -unit=M -path="/home/archivos/fase2/D1.disk" -fit=FF
mkdisK -sizE=120 -unit=M -path="/home/archivos/fase2/D2.disk" -fit=FF

#Crearemos las mismas 12 particiones en elprimer disco
#PrimarIA 1 es de 20 Mb
#PrimarIA 2 es de 10 Mb
#PrimarIA 3 es de 10 Mb


fdisk -sizE=20 -UniT=M -path="/home/archivos/fase2/D1.disk" -type=P -fit=FF -name="PRI1"
fdisk -path="/home/archivos/fase2/D1.disk" -sizE=10000 -fit=BF -name="PRI2"
fdisk -unit=M -path="/home/archivos/fase2/D1.disk" -sizE=10 -name="PRI3"
#Crearemos las mismas 12 particiones en el segundo disco
#PrimarIA 1 es de 10 Mb
#PrimarIA 2 es de 10 Mb
#PrimarIA 3 es de 10 Mb

fdisk -sizE=10 -UniT=M -path="/home/archivos/fase2/D2.disk" -type=P -fit=FF -name="PRI1"
fdisk -path="/home/archivos/fase2/D2.disk" -sizE=10000 -fit=BF -name="PRI2"
fdisk -unit=M -path="/home/archivos/fase2/D2.disk" -sizE=10 -name="PRI3"
#Debería generar los ids: vda1, vdb1, vda2, vdb2, vda3, vdb3
#vda para el D2.disk y vdb para d1.disk
mouNt -NamE="PRI1"  -path="/home/archivos/fase2/D2.disk"
moUnt -PAth="/home/archivos/fase2/D2.disk" -name="PRI2"
mouNt -path="/home/archivos/fase2/D1.disk" -NamE="PRI1"
moUnt -name="PRI2" -PAth="/home/archivos/fase2/D1.disk"


#Crea el sistema de archivos EXT3 en todas las particiones primarias PRI1 
mkfs -id=vda1 -type=Full 
Mkfs -id=vdb1 
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


#nos logueamos en la particion PRI1 con nuestro usuario root, cambiar pwd a su no.carne
loGin -usr=root -pwd=123 -id=vdb1
#Crearemos un grupo llamado "MySql" ,"Oracle" y "DB2"
mkgrp -name="MySql"
mkgrp -name="Oracle"
mkgrp -name="DB2"
#Crearemos 3 usuarios llamados user1, user2 y user3
Mkusr -usr="user4" -grp=MySql -pwd=123
Mkusr -usr="user5" -grp=Oracle -pwd=123
Mkusr -usr="user6" -grp=MySql -pwd=123




#Cerramos sesión e iniciamos sesión con user1 en vda1-----------------------------------------------------
LogouT
loGin -usr=user1 -pwd=user1 -id=vda1
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
mkdir -path="/home/archivos/mia/fase2/a1"
mkdir -path="/home/archivos/mia/fase2/a2"
mkdir -path="/home/archivos/mia/fase2/a3"
mkdir -path="/home/archivos/mia/fase2/a4"
mkdir -path="/home/archivos/mia/fase2/a5"
mkdir -path="/home/archivos/mia/fase2/a6"
mkdir -path="/home/archivos/mia/fase2/a7"
mkdir -path="/home/archivos/mia/fase2/a8"
mkdir -path="/home/archivos/mia/fase2/a9"
mkdir -path="/home/archivos/mia/fase2/a10"
mkdir -path="/home/archivos/mia/fase2/a11"
mkdir -path="/home/archivos/mia/fase2/a12"
mkdir -path="/home/archivos/mia/fase2/a13"
mkdir -path="/home/archivos/mia/fase2/a14"
mkdir -path="/home/archivos/mia/fase2/a15"
mkdir -path="/home/archivos/mia/fase2/a16"
mkdir -path="/home/archivos/mia/fase2/a17"
mkdir -path="/home/archivos/mia/fase2/a18"
mkdir -path="/home/archivos/mia/fase2/a19"
mkdir -path="/home/archivos/mia/fase2/a20"
mkdir -path="/home/archivos/mia/fase2/a21"
mkdir -path="/home/archivos/mia/fase2/a22"
mkdir -path="/home/archivos/mia/fase2/a23"
mkdir -path="/home/archivos/mia/fase2/a24"
mkdir -path="/home/archivos/mia/fase2/a25"



mkFile -SIZE=100 -PatH="/home/archivos/mia/fase2/archivito/a.txt" -p
mkfile -path="/home/b.txt" -SIZE=100
#DEBE CREAR EL archivo arch.txt en su compu o concatenar el contenido del cont como sea esta bien -----
mkfile -path=/home/c.txt -p -cont="/home/arch.txt" 


#EDITAR ARCHIVO fase1.txt
#edit -path="/home/archivos/mia/fase2/archivito/a.txt" -cont ="Hola mundo :D Que buena la vida despues de ganar archivos :D"
#edit -path="/home/c.txt" -cont ="agregue Contenido a c.txt"




#Crearemos la ruta y las padres que no existan
mkdir -path="/home/archivos/mia/fase2" -p
mkdir -path="/home/archivos/mia/carpeta2" -p
mkdir -path="/home/archivos/mia/carpeta2/b1"
mkdir -path="/home/archivos/mia/carpeta2/b2"
mkdir -path="/home/archivos/mia/carpeta2/b3"
mkdir -path="/home/archivos/mia/carpeta2/b4"
mkdir -path="/home/archivos/mia/carpeta2/b5"
mkdir -path="/home/archivos/mia/carpeta2/b6"
mkdir -path="/home/archivos/mia/carpeta2/b7"
mkdir -path="/home/archivos/mia/carpeta2/b8"
mkdir -path="/home/archivos/mia/carpeta2/b9"
mkdir -path="/home/archivos/mia/carpeta2/b10"


#rep -name=tree -Path="/home/wrm/Tree.jpg" -id=vda1

pause
syncronice -id=vda1
#pause
