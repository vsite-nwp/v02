#### vježba 2

Zadane su (u namespace-u vsite::nwp) gotove klase
*	application  - globalne stvari poput petlje poruka
*	window   - bazna klasa za sve vrste prozora

Napišite program koji sadrži listbox, edit i dva buttona „Add“ i Remove“. Klik na „Add“ dodaje tekst iz edita u listbox, klik na „Remove“ briše selektirani red u listboxu

![main window](/v2.JPG?raw=true)

Uputstva:
*	klase button, edit, list_box izvedite iz klase window i prepišite funkciju class_name
*	klasu za glavni prozor izvedite iz window 
*	u on_create() napravite sve child prozore
*	u on_destroy() osigurajte izlazak iz programa
*	u on_command() odgovarate na sve komande
*	u WinMain napravite glavni prozor i objekt klase Application
*	tekst iz edit kontrole možete dobiti sa [GetDlgItemText](https://msdn.microsoft.com/en-us/library/windows/desktop/ms645489%28v=vs.85%29.aspx)
*	poruke koje ćete koristiti za listbox: [LB_ADDSTRING](https://msdn.microsoft.com/en-us/library/windows/desktop/bb775181%28v=vs.85%29.aspx), [LB_DELETESTRING](https://msdn.microsoft.com/en-us/library/windows/desktop/bb775183%28v=vs.85%29.aspx), [LB_GETCURSEL](https://msdn.microsoft.com/en-us/library/windows/desktop/bb775197%28v=vs.85%29.aspx)
*	poruke child prozorima možete slati sa [SendDlgItemMessage](https://msdn.microsoft.com/en-us/library/windows/desktop/ms645515%28v=vs.85%29.aspx)

