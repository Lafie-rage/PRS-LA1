int main(void) {
  struct nombre_complexe {
    double partReelle;
    double partImaginaire;
  } z;
  z.partReelle=1;
  z.partImaginaire=2;
  return z.partReelle;
}
