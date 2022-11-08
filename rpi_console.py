import tkinter as tk
import random
import pymongo

bin1_level = None
bin2_level = None


def poll():
    global bin1_level
    global bin2_level

    try:
        # read from mongodb
        with pymongo.MongoClient('mongodb://localhost:27017/') as client:
            db = client['bin_db']
            collection = db['bin_collection']
            response = collection.find()
            for item in response:
                if item['bin_id'] == 'A':
                    # data for bin 1 taken from the db
                    bin1_level.set(int(item['fill_level']))
                if item['bin_id'] == 'B':
                    # data for bin 2 taken from the db
                    bin2_level.set(int(item['fill_level']))
            # data for bin 2 generated using random numbers
            # bin2_level.set(random.randint(30, 40))
    except:
        pass
    root.after(2000, poll)


root = tk.Tk()
root.title("MAIN WINDOW")
root.resizable(0, 0)

bin1_level = tk.IntVar()
bin2_level = tk.IntVar()

label_bin1 = tk.Label(root, text="BIN I", font=("Comic Sans MS", 20))
label_bin2 = tk.Label(root, text="BIN II", font=("Comic Sans MS", 20))
label_fill1 = tk.Label(root, text="fill level", font=("Comic Sans MS", 20))
label_fill2 = tk.Label(root, text="fill level", font=("Comic Sans MS", 20))

label_bin1_level = tk.Label(root, textvariable=bin1_level, bg="white", font=("Comic Sans MS", 20))
label_bin2_level = tk.Label(root, textvariable=bin2_level, bg="white", font=("Comic Sans MS", 20))
button_quit = tk.Button(root, text="Quit", command=root.destroy, font=("Comic Sans MS", 20))

label_bin1.grid(row=0, column=0, padx=70, pady=70)
label_fill1.grid(row=2, column=0, padx=70, pady=70)
label_fill2.grid(row=2, column=1, padx=70, pady=70)
label_bin2.grid(row=0, column=1, padx=70, pady=70)
label_bin1_level.grid(row=1, column=0, padx=70, pady=70)
label_bin2_level.grid(row=1, column=1, padx=70, pady=70)
button_quit.grid(row=3, column=0, padx=70, pady=70)

root.after(2000, poll)
root.mainloop()
