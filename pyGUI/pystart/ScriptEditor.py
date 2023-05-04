'''**************************************************************************************
 **************************************************************************************
 ______________________________________________________________________________________

  Company:
	Synapticon GmbH (https://www.synapticon.com/)
 ______________________________________________________________________________________

  File Name:
	Datatype.xc
 ______________________________________________________________________________________

  Summary:
    This file contains the source code for testing all the data types and 
    their memory allocated size assigned by the xc compiler.
 ______________________________________________________________________________________

  Description:
	This file contains the source code for a self-practice task by Synapticon GmbH. 
    It implements the logic of the application's requirements, and it may call API 
    routines from a different section of the code, such as drivers, system services, 
    and middleware (if applicable). However, at present, this code is not calling 
    any of the system-specified APIs (such as the "USARTInitialize" and "TimerTasks"
    functions) of any of the modules in the system. To make the code development 
    environment-friendly, the majority of the code shall be using self-created drivers.

 **************************************************************************************
 **************************************************************************************/

 /**************************************************************************************
   No-Copyright (c):
	 No copyrights are being imposed on these software files. Information shall have
	 to be freely available for the rapid development of science to benefit humanity.
	 When the information is free, this is not a barrier to their progress. Therefore,
	 I, Aatif Shaikh, license you the right to use, modify, copy and distribute this
	 software however you desire.

	 Note*
	 Software and documentation are provided "as is" without warranty of any kind,
	 either express or implied, including without limitation, any warranty of
	 merchantability, title, non-infringement and fitness for a particular purpose.
	 In no event shall, I (Aatif Shaikh) liable or obligated under contract,
	 negligence, strict liability, contribution, breach of warranty, or other legal
	 equitable theory any direct or indirect damages or expenses including but not
	 limited to any incidental, special, indirect, punitive or consequential damages,
	 lost profits or lost data, cost of procurement of substitute goods, technology,
	 services, or any claims by third parties (including but not limited to any
	 defence thereof), or other similar costs.

  ************************************************************************************/

  /************************************************************************************
  ______                                            __      __                                     
 /      \                                          |  \    |  \                                    
|  $$$$$$\ __    __  _______    ______    ______  _| $$_    \$$  _______   ______   _______        
| $$___\$$|  \  |  \|       \  |      \  /      \|   $$ \  |  \ /       \ /      \ |       \       
 \$$    \ | $$  | $$| $$$$$$$\  \$$$$$$\|  $$$$$$\\$$$$$$  | $$|  $$$$$$$|  $$$$$$\| $$$$$$$\      
 _\$$$$$$\| $$  | $$| $$  | $$ /      $$| $$  | $$ | $$ __ | $$| $$      | $$  | $$| $$  | $$      
|  \__| $$| $$__/ $$| $$  | $$|  $$$$$$$| $$__/ $$ | $$|  \| $$| $$_____ | $$__/ $$| $$  | $$      
 \$$    $$ \$$    $$| $$  | $$ \$$    $$| $$    $$  \$$  $$| $$ \$$     \ \$$    $$| $$  | $$      
  \$$$$$$  _\$$$$$$$ \$$   \$$  \$$$$$$$| $$$$$$$    \$$$$  \$$  \$$$$$$$  \$$$$$$  \$$   \$$      
          |  \__| $$                    | $$                                                       
           \$$    $$                    | $$                                                       
            \$$$$$$                      \$$                                                       
                          ______                 __        __    __                                
                         /      \               |  \      |  \  |  \                               
                        |  $$$$$$\ ______ ____  | $$____  | $$  | $$                               
                        | $$ __\$$|      \    \ | $$    \ | $$__| $$                               
                        | $$|    \| $$$$$$\$$$$\| $$$$$$$\| $$    $$                               
                        | $$ \$$$$| $$ | $$ | $$| $$  | $$| $$$$$$$$                               
                        | $$__| $$| $$ | $$ | $$| $$__/ $$| $$  | $$                               
                         \$$    $$| $$ | $$ | $$| $$    $$| $$  | $$                               
                          \$$$$$$  \$$  \$$  \$$ \$$$$$$$  \$$   \$$                               
                                                                                                   
                                                                                                                                                                                                   
		        In order to be irreplaceable, one must always be different
  *************************************************************************************'''
# * ----------------------------------------------------------------------------
# *                           imports
# * ----------------------------------------------------------------------------

from   tkinter    import *
from   tkinter    import messagebox
from   tkinter.filedialog import askopenfilename, asksaveasfilename
import tkinter.ttk as ttk
import subprocess
import threading
import time
import os

# * ----------------------------------------------------------------------------
# *                           constants and definition
# * ----------------------------------------------------------------------------

Application_Title = "MicroPython On XMOS"

# * ----------------------------------------------------------------------------
# *                           Variables
# * ----------------------------------------------------------------------------

CurrentFile = ""
HandlerTextArea  = None
HandlerPrintArea = None


# * ----------------------------------------------------------------------------
# *                           Manage the text area
# * ----------------------------------------------------------------------------

'''-------------------------------------------------------------------------------
 Function Name: FnSaveTheFile
 Argument: None
 Return: None
 Note: This function delete (trunc) the text area of the new file
-------------------------------------------------------------------------------'''

def highlight_python_code(event=None):
    keywords = ['and', 'as', 'assert', 'break', 'class', 'continue',
                'def', 'del', 'elif', 'else', 'except', 'False',
                'finally', 'for', 'from', 'global', 'if', 'import',
                'in', 'is', 'lambda', 'None', 'nonlocal', 'not',
                'or', 'pass', 'raise', 'return', 'True', 'try',
                'while', 'with', 'yield',r'["\']([^"\']*)["\']']

    HandlerTextArea.tag_remove('keyword', '1.0', 'end')
    for keyword in keywords:
        start = '1.0'
        while True:
            pos = HandlerTextArea.search(keyword, start, stopindex='end', regexp = True)
            if not pos:
                break
            end = f'{pos}+{len(keyword)}c'
            HandlerTextArea.tag_add('keyword', pos, end)
            start = end


# * ----------------------------------------------------------------------------
# *                           Menul design
# * ----------------------------------------------------------------------------
class TextScrollCombo(ttk.Frame):

    def __init__(root, *args, **kwargs):
        super().__init__(*args, **kwargs)

    # ensure a consistent GUI size
        root.grid_propagate(False)
    # implement stretchability
        root.grid_rowconfigure   (0, weight=1)
        root.grid_columnconfigure(0, weight=1)

    # create a Text widget
        root.textboxhandler = Text(root)
        root.textboxhandler.grid(row=0, column=0, sticky="nsew", padx=2, pady=2)

    # create a Scrollbar and associate it with txt
        scrollb = ttk.Scrollbar(root, command=root.textboxhandler.yview)
        scrollb.grid(row=0, column=1, sticky='nsew')
        root.textboxhandler['yscrollcommand'] = scrollb.set


# * ----------------------------------------------------------------------------
# *                           Files handing feature
# * ----------------------------------------------------------------------------

'''-------------------------------------------------------------------------------
 Function Name: FnSaveTheFile
 Argument: None
 Return: None
 Note: This function delete (trunc) the text area of the new file
-------------------------------------------------------------------------------'''
def FnCreateANewFile(root,HandlerTextArea):
    global CurrentFile
    root.title("Untitled - Notepad")
    CurrentFile = None
    HandlerTextArea.delete(1.0, END)

    global file
    CurrentFile = askopenfilename(defaultextension=".txt",
                           filetypes=[("All Files", "*.*"),
                                     ("Text Documents", "*.txt")])

'''-------------------------------------------------------------------------------
 Function Name: FnSaveTheFile
 Argument: None
 Return: None
 Note: This function delete (trunc) the text area of the new file
-------------------------------------------------------------------------------'''
def FnOpenTheFile(root,HandlerTextArea):
    global CurrentFile
    CurrentFile = askopenfilename(defaultextension=".txt",
                           filetypes=[("All Files", "*.*"),
                                     ("Text Documents", "*.txt")])
    if CurrentFile == "":
        CurrentFile = None
    else:
        root.title(os.path.basename(CurrentFile) + " - Notepad")
        HandlerTextArea.delete(1.0, END)
        f = open(CurrentFile, "r")
        HandlerTextArea.insert(1.0, f.read())
        f.close( )

'''-------------------------------------------------------------------------------
 Function Name: FnSaveTheFile
 Argument: None
 Return: None
 Note: This function delete (trunc) the text area of the new file
-------------------------------------------------------------------------------'''
def FnSaveTheFile(root,HandlerTextArea ):
    global CurrentFile
    if CurrentFile == None:
        CurrentFile = asksaveasfilename(initialfile = 'Untitled.txt', defaultextension=".txt",
                           filetypes=[("All Files", "*.*"),
                                     ("Text Documents", "*.txt")])
        if CurrentFile =="":
            CurrentFile = None

        else:
            #Save as a new file
            f = open(CurrentFile, "w")
            f.write(HandlerTextArea.get(1.0, END))
            f.close()

            root.title(os.path.basename(CurrentFile) + " - Notepad")
            print("File Saved")
    else:
        # Save the file
        f = open(CurrentFile, "w")
        f.write(HandlerTextArea.get(1.0, END))
        f.close( )

'''-------------------------------------------------------------------------------
 Function Name: FnSaveTheFile
 Argument: None
 Return: None
 Note: This function delete (trunc) the text area of the new file
-------------------------------------------------------------------------------'''
def FnConvertTheScript(script):
    Convo = ""
    for line in script.splitlines():
        if (len(line) >= 2):
            Convo = Convo + '"' + line + '\\' + 'n"' + '\n'
    return 'char scScript [] =' + Convo + ';'
             
'''-------------------------------------------------------------------------------
 Function Name: FnSaveTheFile
 Argument: None
 Return: None
 Note: This function delete (trunc) the text area of the new file
-------------------------------------------------------------------------------'''
def FnPrintThetext(root,HandlerTextArea,HandlerPrintArea):
    

    if ( CurrentFile == None): #check if the file is opened/ selected or not
         messagebox.showerror('File Error', 'File not saved or selected')
    else:
        if len(HandlerTextArea.get("1.0",END)) >= 10 : #check if there is minimum one like in the code file
            UpdatedScript = FnConvertTheScript(HandlerTextArea.get("1.0",END))
            with open('script.h', 'w') as ScriptFile:
                 ScriptFile.write(UpdatedScript)
                 ScriptFile.close()    
                 os.system("make clean && make")
                 os.system('xrun --io output.xe')
                 
        else :
            messagebox.showerror('File Error', 'This File is either empty or has fewer commands')

# * ----------------------------------------------------------------------------
# *                           Menu options
# * ----------------------------------------------------------------------------
'''-------------------------------------------------------------------------------
 Function Name: FnSaveTheFile
 Argument: None
 Return: None
 Note: This function delete (trunc) the text area of the new file
-------------------------------------------------------------------------------'''
def FnQuitTheApp(root):
    root.destroy()
'''-------------------------------------------------------------------------------
 Function Name: FnSaveTheFile
 Argument: None
 Return: None
 Note: This function delete (trunc) the text area of the new file
-------------------------------------------------------------------------------'''
def cut(HandlerTextArea):
    HandlerTextArea.event_generate(("<>"))
'''-------------------------------------------------------------------------------
 Function Name: FnSaveTheFile
 Argument: None
 Return: None
 Note: This function delete (trunc) the text area of the new file
-------------------------------------------------------------------------------'''
def copy(HandlerTextArea):
    HandlerTextArea.event_generate(("<>"))
'''-------------------------------------------------------------------------------
 Function Name: FnSaveTheFile
 Argument: None
 Return: None
 Note: This function delete (trunc) the text area of the new file
-------------------------------------------------------------------------------'''
def paste(HandlerTextArea):
    HandlerTextArea.event_generate(("<>"))
'''-------------------------------------------------------------------------------
 Function Name: FnSaveTheFile
 Argument: None
 Return: None
 Note: This function delete (trunc) the text area of the new file
-------------------------------------------------------------------------------'''
def about():
    messagebox.showinfo("Notepad", "still in development")    

# * ----------------------------------------------------------------------------
# *                           Main code
# * ----------------------------------------------------------------------------
if __name__ == '__main__':

    CurrentFile = None #clear/ reset the file name
    root = Tk( ) #init the Tkinter
    root.title("Untitled - Notepad") #Set the default title
    #root.geometry("2560x2000") # Geometry
    root.resizable(0, 0)

    combo = TextScrollCombo(root)
    combo.pack(fill="both", expand=True)
    combo.config(width=1800, height=650)
    combo.textboxhandler.config(font=("consolas", 12), undo=True, wrap='word')
    combo.textboxhandler.config(borderwidth=3, relief="sunken")
    # Configure the tags for Python syntax highlighting
    combo.textboxhandler.tag_configure('keyword', foreground='blue')
    combo.textboxhandler.tag_configure('strings', foreground='green')
    combo.textboxhandler.bind('<KeyRelease>', highlight_python_code)

    HandlerTextArea= combo.textboxhandler

    combo1 = TextScrollCombo(root)
    combo1.pack(fill="both", expand=True)
    combo1.config(width=1800, height=300)
    combo1.textboxhandler.config(font=("consolas", 12), undo=True, wrap='word')
    combo1.textboxhandler.config(borderwidth=3, relief="sunken", state=DISABLED)
    HandlerPrintArea= combo.textboxhandler


    MenuBar  = Menu(root) #create a menubar
    FileMenu = Menu(MenuBar, tearoff=0) #File Menu Starts

    FileMenu.add_command(label ="New",  command=lambda: FnCreateANewFile(root,HandlerTextArea))# To open new file
    FileMenu.add_command(label ="Open", command=lambda: FnOpenTheFile(root,HandlerTextArea))#To Open already existing file
    FileMenu.add_command(label ="Save", command=lambda: FnSaveTheFile(root,HandlerTextArea)) # To save the current file
    FileMenu.add_separator( ) # adds a seperation line
    FileMenu.add_command(label ="Exit", command=lambda: FnQuitTheApp(root))
    MenuBar.add_cascade(label  ="File", menu=FileMenu) # File Menu ends

    # Edit Menu Starts
    EditMenu = Menu(MenuBar, tearoff=0)
    #To give a feature of cut, copy and paste
    EditMenu.add_command(label = "Cut",  command=cut  )
    EditMenu.add_command(label = "Copy", command=copy )
    EditMenu.add_command(label = "Paste",command=paste)
    MenuBar.add_cascade(label="Edit", menu = EditMenu )
    # Edit Menu Ends

    # Help Menu Starts
    HelpMenu = Menu(MenuBar, tearoff=0)
    HelpMenu.add_command(label = "About Notepad", command=about)
    MenuBar.add_cascade(label="Help", menu=HelpMenu)
    # Help Menu Ends

    #run menu starts
    RunMenu = Menu(MenuBar, tearoff=0)
    RunMenu.add_command(label = "Compile and Run", command= lambda: FnPrintThetext(root,HandlerTextArea,HandlerPrintArea))
    MenuBar.add_cascade(label="Run", menu=RunMenu)

    root.config(menu=MenuBar)

    root.mainloop( )