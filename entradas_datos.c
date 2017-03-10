int error() {
  printf("Respuesta no valida, vuelva a intentarlo\n");
  return 0;
}

int strget(char *buffer, int max_length) {
  int i, c;
  c = getc(stdin);
  max_length--;
  for (i=0; i < max_length && c != EOF && c != '\n'; i++) {
    buffer[i] = c;
    c = getc(stdin);
  }
  buffer[i] = 0;
  // vacea el buffer si se intro dujo mas caracteres de los pedidos
  if(i == max_length) {
    while(c != EOF && c != '\n')
      c = getc(stdin);
  }
  return i;
}

int get_char() {
  int l, l2;
  l = getc(stdin);
  while(l2 != EOF && l2 != 10)
    l2 = getc(stdin);
  return l;
}

int get_num(int *_p) {
  int length = 5;
  char num[length];

  strget(num, length);
  *_p = atoi(num);
  return *_p;
}

int entrada_letra(int *e, int x){
  int val;
  while(1){
    val = toupper(get_char());
    // hacer val -= 1 es lo mismo que val = val - 1
    if(val >= 65 && val <= 90)
      val -= 64;
    else
      error();

    if(val <= x) {
      break;
      val--;
    }
  }
  // vacea el buffer si se intro dujo mas de un caracteres
  *e = val;
  return val;
}

int entrada_numero(int *i, int x) {
  int val;
  get_num(&val);
  while(val <= 0 || val > x) {
    error();
    get_num(&val);
  }
  *i = val;
  return val;
}