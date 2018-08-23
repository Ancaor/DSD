
Práctica realizada por Antonio José Camarero Ortega


Comando para la ejecución del servidor :
 
    $   node servidor.js
    
    
Para la ejecución de los clientes:

    Cliente : http://localhost:8080/
    
    Sensores : http://localhost:8080/sensores.html
    
    Agente : http://localhost:8080/agente.html
    
Recordar que para el funcionamiento de alertas es necesario que el Agente esté abierto en el navegador.

Con sensores.html se introducen valores de temperatura e iluminación.

Los valores maximo y minimo de temperatura e iluminación son:

        temp_maxima = 25;
        luz_maxima = 30;
        
        temp_minima = 5;
        luz_minima = 0;
        
Si el sensor detecta valores por encima o por debajo de los limites saltan alertas.
        
        
   /*****************     EXAMEN    **********************/
        
        
Para que se encienda el aspersor han de darse estas dos condiciones:

        temperatura <= 25 
        ht < 10
        
SI no se dan las dos condiciones y el aspersor estaba encendido se apagará automaticamente.
        

En el codigo se ha incluido comentarios del tipo //EXAMEN en las partes del código modificadas.

Las partes tocadas han sido :

    -Agente : Creados valores de ht, y se ha modificado el método que se dispara cuando se llama a actualizar_temperatura y se ha creado el método
              actualizar_humedad_tierra para que comprueben si ha de saltar alarma o no.
              
    -CLiente : Añadido el accionador del aspersor y alertas.
    
    -Servidor : Todo lo necesario para que se guarde en la BD la información de la humedad de la tierra y poder cocnsultarla.
    
    -Sensores : Formulario para obtener información del sensor de humedad de tierra.
        
        

    
