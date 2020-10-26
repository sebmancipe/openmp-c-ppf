#!/usr/bin/perl

# Archivo: launcher.pl
# Autores: Anderson Ballesteros <anderson.ballesteros@correo.usa.edu.co>
#          Sebastian Mancipe <sebastian.mancipe@correo.usa.edu.co>
# Última Modificación: 13 de Octubre, 2020

# Este script ejecuta una serie de programas pasándole cargas e hilos según los arreglos
# programas, cargas y threads, respectivamente.
# Toma el resultado entregado por estos y les saca un promedio
# Los promedios se guardan en una carpeta por programa:
# launcher.pl
# algorithm_1.results
#     |______algorithm_1_144_output.txt
#     |______algorithm_1_288_output.txt
#	  |______algorithm_1_576_output.txt
# algorithm_2.results
#     |______algorithm_2_144_output.txt
#     |______algorithm_2_288_output.txt
#	  |______algorithm_2_576_output.txt
#
# Cada archivo txt tiene el promedio separado por número de hilos


@programas = ("algorithm_1", "algorithm_2", "algorithm_3"); # nombres de los archivos
@cargas = (144, 288, 576, 720, 960, 1440, 1920);
@threads = (2, 4, 6, 8, 12);
$rep = 20; #repeticiones

print "Cleaning .results folder if exist...\n";
system("rm -rf *.results"); #Eliminar carpetas generadas por el script anteriormente

print "Making files...\n";
system("make -s"); #Ejecutar el archivo makefile en el directorio donde se encuentra el script

foreach $programa (@programas){
	$dir = "$programa.results"; #Carpeta donde se almancenarán los resultados de cada programa
	system("mkdir ".$dir);
	print "Starting ".$programa." execution...\n";
	foreach $carga (@cargas) {
		$outputFile = $programa."_".$carga."_output.txt";
		print "Working with load ".$carga." ...\n";
		foreach $thread (@threads){
			system("echo Thread = $thread >> $dir/$outputFile");
			$sum = 0;
			for ($i=0; $i<$rep; $i++) {
				$out = `./$programa $carga $thread`;
				$sum += $out;
			}
			$avg = $sum/$rep;
			system("echo $avg >> $dir/$outputFile");
		}
	}
	print "Finished ".$programa." execution...\n";
}
