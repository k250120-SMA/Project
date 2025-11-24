import tkinter as tk
import ctypes
import os

SIZE = 4

# load DLL
dll_path = os.path.abspath("game2048.dll")
game = ctypes.CDLL(dll_path)

# define board type for ctypes
BoardType = (ctypes.c_int * SIZE) * SIZE

# set function signatures
game.Boardinit.argtypes = [BoardType]
game.AddTile.argtypes = [BoardType]
game.move_left.argtypes = [BoardType]
game.move_right.argtypes = [BoardType]
game.move_up.argtypes = [BoardType]
game.move_down.argtypes = [BoardType]
game.GameStateCheck.argtypes = [BoardType]
game.check_win.argtypes = [BoardType]
game.maxTile.argtypes = [BoardType]
game.getScore.restype = ctypes.c_int
game.resetScore.argtypes = []

# GUI colors
COLORS = {
    0: "#cdc1b4",
    2: "#eee4da",
    4: "#ede0c8",
    8: "#f2b179",
    16: "#f59563",
    32: "#f67c5f",
    64: "#f65e3b",
    128: "#edcf72",
    256: "#edcc61",
    512: "#edc850",
    1024: "#edc53f",
    2048: "#edc22e"
}

root = tk.Tk()
root.title("2048 - C Logic Connected")

frame = tk.Frame(root, bg="#bbada0")
frame.pack(pady=20)

cells = []
board = BoardType()

def update_gui():
    for r in range(SIZE):
        for c in range(SIZE):
            val = board[r][c]
            cells[r][c].config(
                text=str(val) if val != 0 else "",
                bg=COLORS.get(val, "#3c3a32")
            )
    score_label.config(text=f"Score: {game.getScore()}")

def restart():
    game.resetScore()
    game.Boardinit(board)
    update_gui()

def move_left():
    moved = game.move_left(board)
    if moved:
        game.AddTile(board)
    update_gui()

def move_right():
    moved = game.move_right(board)
    if moved:
        game.AddTile(board)
    update_gui()

def move_up():
    moved = game.move_up(board)
    if moved:
        game.AddTile(board)
    update_gui()

def move_down():
    moved = game.move_down(board)
    if moved:
        game.AddTile(board)
    update_gui()

def key(event):
    if event.keysym == "Left":
        move_left()
    elif event.keysym == "Right":
        move_right()
    elif event.keysym == "Up":
        move_up()
    elif event.keysym == "Down":
        move_down()

    if game.check_win(board):
        tk.messagebox.showinfo("2048", "You reached 2048!")
    if game.GameStateCheck(board):
        tk.messagebox.showinfo("Game Over", "No more moves!")

root.bind("<Key>", key)

score_label = tk.Label(root, text="Score: 0", font=("Helvetica", 20))
score_label.pack()

restart_btn = tk.Button(root, text="Restart", font=("Helvetica", 16), command=restart)
restart_btn.pack(pady=10)

for i in range(SIZE):
    row = []
    for j in range(SIZE):
        label = tk.Label(frame, text="", width=4, height=2,
                         font=("Helvetica", 28, "bold"),
                         bg=COLORS[0], fg="#776e65")
        label.grid(row=i, column=j, padx=5, pady=5)
        row.append(label)
    cells.append(row)

game.Boardinit(board)
update_gui()

root.mainloop()