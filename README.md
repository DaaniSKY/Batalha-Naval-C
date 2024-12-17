# Batalha-Naval-C
Trabalho da Faculdade

Foi substituido a linha de código 
if (playerAttack(x, y) == 1) {
    playerHits++;
} 
para está linha código
if (displayBoard[x][y] == 'H') {
    playerHits++;
} 
não dava certo antes pois chamava duas vezes a variavel playerAttack
