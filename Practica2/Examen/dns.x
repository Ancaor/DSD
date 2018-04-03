/* archivo calculadora.x: Paso de argumento estilo C */
program DNSPROG {
  version DNSCVER {
    int registrar (string, string) = 1;
    int eliminar (string) = 2;
    string buscar (string) = 3;
    int modificar(string,string,int) = 4;
  } = 1;
} = 0x20000199;
