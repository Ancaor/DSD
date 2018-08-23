var http = require("http");
var url = require("url");
var fs = require("fs");
var path = require("path");
var socketio = require("socket.io");

var MongoClient = require('mongodb').MongoClient;
var mimeTypes = { "html": "text/html", "jpeg": "image/jpeg", "jpg": "image/jpeg", "png": "image/png", "js": "text/javascript", "css": "text/css", "swf": "application/x-shockwave-flash"};


// El servidor ofrece la página cliente.html al conectarse
var httpServer = http.createServer(
	function(request, response) {
		var uri = url.parse(request.url).pathname;
		if (uri=="/") uri = "/cliente.html";
		var fname = path.join(process.cwd(), uri);
		fs.exists(fname, function(exists) {
			if (exists) {
				fs.readFile(fname, function(err, data){
					if (!err) {
						var extension = path.extname(fname).split(".")[1];
						var mimeType = mimeTypes[extension];
						response.writeHead(200, mimeType);
						response.write(data);
						response.end();
					}
					else {
						response.writeHead(200, {"Content-Type": "text/plain"});
						response.write('Error de lectura en el fichero: '+uri);
						response.end();
					}
				});
			}
			else{
				console.log("Peticion invalida: "+uri);
				response.writeHead(200, {"Content-Type": "text/plain"});
				response.write('404 Not Found\n');
				response.end();
			}
		});
	}
);

// Estados de la persiana y el ac, por defecto activos
var estado_persiana = 'abierta';
var estado_ac = 'activo';
var estado_luz = 'encendida';
var estado_aspersor = 'apagado';  //EXAMEN

// Conexión a la base de datos
MongoClient.connect("mongodb://localhost:27017/", function(err, db) {
	if(!err){
		console.log("Conectado a Base de Datos");
	}
	var dbo = db.db("pruebaBaseDatos");
	var msgCliente = null;

	httpServer.listen(8080); // Ponemos el servidor a escuchar en el puerto 8080

	var io = socketio.listen(httpServer); // Ponemos los sockets a escuchar en el servidor
	
	dbo.createCollection("sensores", function(err, collection){
		io.sockets.on('connection',function(client) {

			// publica datos desde sensores a base de datos
	    	client.on('publicar', function(data) {
	    		// Insertamos los datos en la colección
				collection.insert(data, {safe:true}, function(err, result) {});
		
				// Actualizamos todos los clientes añadiendo los últimos datos
				io.sockets.emit('actualizar', 
					"temperatura: " + data.temperatura + 
					", luminosidad: " + data.luminosidad + 
					", humedad_tierra: " + data.humedadTierra +          //EXAMEN
					", fecha: "+ data.time );

				io.sockets.emit('actualizar_temp', data.temperatura);
				io.sockets.emit('actualizar_luz', data.luminosidad);
				io.sockets.emit('actualizar_humedad_tierra', data.humedadTierra);   //EXAMEN
				
			});

	    	// El cliente obtiene datos de la base de datos
	    	client.on('obtener', function () {
				collection.find().sort({_id:-1}).limit(1).forEach(function(result){
					client.emit('actualizar', 
						"temperatura: " + result.temperatura + 
						", luminosidad: " + result.luminosidad + 
						", humedad_tierra: " + result.humedadTierra + 						//EXAMEN
						", fecha: "+ result.time );

				});
			});

	    	// Manda al cliente a actualizar su temperatura ( lo manda el agente para detectar alertas)
			client.on('obtener_temp', function () {
				collection.find().sort({_id:-1}).limit(1).forEach(function(result){
					client.emit('actualizar_temp',result.temperatura);
				});
			});

			// Manda al cliente a actualizar su iluminacion ( lo manda el agente para detectar alertas)
			client.on('obtener_luz', function () {
				collection.find().sort({_id:-1}).limit(1).forEach(function(result){
					client.emit('actualizar_luz',result.luminosidad);
				});
			});



			//EXAMEN
			// Manda al cliente a actualizar su humedad ( lo manda el agente para detectar alertas)
			client.on('obtener_humedad', function () {
				collection.find().sort({_id:-1}).limit(1).forEach(function(result){
					client.emit('actualizar_humedad_tierra',result.humedadTierra);
				});
			});



			// Cambia el estado de la persiana
			client.on('cambiar_estado_persiana', function(){
				if (estado_persiana == 'abierta')
					estado_persiana = 'cerrada';
				else
					estado_persiana = 'abierta';

				// Se notifica el nuevo estado a todos los clientes
				io.sockets.emit('actualizar_estado_persiana',estado_persiana);
				console.log("servidor: "+estado_persiana);
			});

			// Cambia el estado del ac
			client.on('cambiar_estado_ac', function(){
				if (estado_ac == 'activo')
					estado_ac = 'apagado';
				else
					estado_ac = 'activo';

				// Se notifica el nuevo estado a todos los clientes
				io.sockets.emit('actualizar_estado_ac',estado_ac);
			});

			// Cambia el estado de la luz
			client.on('cambiar_estado_luz', function(){
				if (estado_luz == 'encendida')
					estado_luz = 'apagada';
				else
					estado_luz = 'encendida';

				// Se notifica el nuevo estado a todos los clientes
				io.sockets.emit('actualizar_estado_luz',estado_luz);
			});

			//EXAMEN
			// Cambia el estado del aspersor
			client.on('cambiar_estado_aspersor', function(){
				if (estado_aspersor == 'encendido')
				estado_aspersor = 'apagado';
				else
				estado_aspersor = 'encendido';

				// Se notifica el nuevo estado a todos los clientes
				io.sockets.emit('actualizar_estado_aspersor',estado_aspersor);
			});


			client.on('obtener_estado_persiana', function(){
				client.emit('actualizar_estado_persiana', estado_persiana);
			});

			client.on('obtener_estado_luz', function(){
				client.emit('actualizar_estado_luz', estado_luz);
			});

			client.on('obtener_estado_aspersor', function(){
				client.emit('actualizar_estado_aspersor', estado_aspersor);
			});


			client.on('obtener_estado_ac', function(){
				client.emit('actualizar_estado_ac', estado_ac);
			});

			client.on('cerrar_persiana', function(){
				estado_persiana = 'cerrada';
				io.sockets.emit('actualizar_estado_persiana', estado_persiana);
				console.log(estado_persiana)
			});

			client.on('abrir_persiana', function(){
				estado_persiana = 'abierta';
				io.sockets.emit('actualizar_estado_persiana', estado_persiana);
				console.log(estado_persiana)
			});

			//EXAMEN

			client.on('encender_aspersor', function(){
				estado_aspersor = 'encendido';
				io.sockets.emit('actualizar_estado_aspersor', estado_aspersor);
				console.log('estado_aspersor = ' + estado_aspersor)
			});
			client.on('apagar_aspersor', function(){
				estado_aspersor = 'apagado';
				io.sockets.emit('actualizar_estado_aspersor', estado_aspersor);
				console.log('estado_aspersor = ' + estado_aspersor)
			});




			// Los siguientes eventos se producen cuando se supera un umbral (tanto superior como inferior) de luminosidad/temperatura
			client.on('alerta_luz_max',function(data){
				io.sockets.emit('actualizar_advertencia_luz_max',data);
			});

			client.on('alerta_luz_min',function(data){
				io.sockets.emit('actualizar_advertencia_luz_min',data);
			});

			client.on('alerta_temp_max',function(data){
				io.sockets.emit('actualizar_advertencia_temp_max',data);
			});

			client.on('alerta_temp_min',function(data){
				io.sockets.emit('actualizar_advertencia_temp_min',data);
			});

			//EXAMEN
			client.on('alerta_ht_min',function(data){
				io.sockets.emit('actualizar_advertencia_ht_min',data);
			});

			client.on('alert_elim_advert_ht',function(){
				io.sockets.emit('eliminar_advertencia_ht');
			});

	    });
    });
});

console.log("Servicio MongoDB iniciado");