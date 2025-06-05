const board = Array.from(document.querySelectorAll('#board div'));
let currentPlayer = 'X'; // Human
let gameOver = false;

// Winning combinations
const winCombos = [
  [0, 1, 2],
  [3, 4, 5],
  [6, 7, 8],
  [0, 3, 6],
  [1, 4, 7],
  [2, 5, 8],
  [0, 4, 8],
  [2, 4, 6]
];

// Add event listeners to each cell
board.forEach((cell, index) => {
  cell.addEventListener('click', () => {
    if (cell.textContent === '' && !gameOver && currentPlayer === 'X') {
      cell.textContent = 'X';
      if (checkWin('X')) {
        alert('Player X wins!');
        gameOver = true;
        return;
      }
      if (isDraw()) {
        alert("It's a draw!");
        gameOver = true;
        return;
      }
      currentPlayer = 'O';
      setTimeout(aiMove, 300);
    }
  });
});

// AI Move using Minimax
function aiMove() {
  const bestMove = findBestMove();
  if (bestMove !== -1) {
    board[bestMove].textContent = 'O';
    if (checkWin('O')) {
      alert('AI wins!');
      gameOver = true;
      return;
    }
    if (isDraw()) {
      alert("It's a draw!");
      gameOver = true;
      return;
    }
    currentPlayer = 'X';
  }
}

function isDraw() {
  return board.every(cell => cell.textContent === 'X' || cell.textContent === 'O');
}

function checkWin(player) {
  return winCombos.some(combo =>
    combo.every(index => board[index].textContent === player)
  );
}

// Minimax implementation
function findBestMove() {
  let bestVal = -Infinity;
  let move = -1;

  for (let i = 0; i < 9; i++) {
    if (board[i].textContent === '') {
      board[i].textContent = 'O';
      let moveVal = minimax(0, false);
      board[i].textContent = '';
      if (moveVal > bestVal) {
        bestVal = moveVal;
        move = i;
      }
    }
  }
  return move;
}

function minimax(depth, isMax) {
  if (checkWin('O')) return 10 - depth;
  if (checkWin('X')) return depth - 10;
  if (isDraw()) return 0;

  if (isMax) {
    let best = -Infinity;
    for (let i = 0; i < 9; i++) {
      if (board[i].textContent === '') {
        board[i].textContent = 'O';
        best = Math.max(best, minimax(depth + 1, false));
        board[i].textContent = '';
      }
    }
    return best;
  } else {
    let best = Infinity;
    for (let i = 0; i < 9; i++) {
      if (board[i].textContent === '') {
        board[i].textContent = 'X';
        best = Math.min(best, minimax(depth + 1, true));
        board[i].textContent = '';
      }
    }
    return best;
  }
}