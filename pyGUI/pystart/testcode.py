import tkinter as tk

def highlight_python_code(event=None):
    keywords = ['and', 'as', 'assert', 'break', 'class', 'continue',
                'def', 'del', 'elif', 'else', 'except', 'False',
                'finally', 'for', 'from', 'global', 'if', 'import',
                'in', 'is', 'lambda', 'None', 'nonlocal', 'not',
                'or', 'pass', 'raise', 'return', 'True', 'try',
                'while', 'with', 'yield',r'["\']([^"\']*)["\']']

    text.tag_remove('keyword', '1.0', 'end')
    for keyword in keywords:
        start = '1.0'
        while True:
            pos = text.search(keyword, start, stopindex='end', regexp = True)
            if not pos:
                break
            end = f'{pos}+{len(keyword)}c'
            text.tag_add('keyword', pos, end)
            start = end

root = tk.Tk()

# Create a Text widget
text = tk.Text(root)

# Configure the tags for Python syntax highlighting
text.tag_configure('keyword', foreground='blue')
text.tag_configure('strings', foreground='green')

# Bind the syntax highlighter function to the <<Modified>> event
text.bind('<KeyRelease>', highlight_python_code)

# Set the syntax highlighting for Python
text.config(
    wrap='word',  # wrap lines at word boundaries
    undo=True,  # enable undo/redo
)

text.pack(expand=True, fill='both')
root.mainloop()