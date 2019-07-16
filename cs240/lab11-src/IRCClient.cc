
#include <stdio.h>
#include <gtk/gtk.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
char * user;
char * password;
char * host;
char * sport;
int port;
#define MAX_RESPONSE (10 * 1024)
char response[MAX_RESPONSE];
GtkListStore * list_rooms;
GtkListStore * user_list;
char * curroom;

//server stuff
int open_client_socket(char * host, int port) {
	// Initialize socket address structure
	struct  sockaddr_in socketAddress;
	
	// Clear sockaddr structure
	memset((char *)&socketAddress,0,sizeof(socketAddress));
	
	// Set family to Internet 
	socketAddress.sin_family = AF_INET;
	
	// Set port
	socketAddress.sin_port = htons((u_short)port);
	
	// Get host table entry for this host
	struct  hostent  *ptrh = gethostbyname(host);
	if ( ptrh == NULL ) {
		perror("gethostbyname");
		exit(1);
	}
	
	// Copy the host ip address to socket address structure
	memcpy(&socketAddress.sin_addr, ptrh->h_addr, ptrh->h_length);
	
	// Get TCP transport protocol entry
	struct  protoent *ptrp = getprotobyname("tcp");
	if ( ptrp == NULL ) {
		perror("getprotobyname");
		exit(1);
	}
	
	// Create a tcp socket
	int sock = socket(PF_INET, SOCK_STREAM, ptrp->p_proto);
	if (sock < 0) {
		perror("socket");
		exit(1);
	}
	
	// Connect the socket to the specified server
	if (connect(sock, (struct sockaddr *)&socketAddress,
		    sizeof(socketAddress)) < 0) {
		perror("connect");
		exit(1);
	}
	
	return sock;
}


int sendCommand(char *  host, int port, char * command, char * response) {
	
	int sock = open_client_socket( host, port);

	if (sock<0) {
		return 0;
	}

	// Send command
	write(sock, command, strlen(command));
	write(sock, "\r\n",2);

	//Print copy to stdout
	write(1, command, strlen(command));
	write(1, "\r\n",2);

	// Keep reading until connection is closed or MAX_REPONSE
	int n = 0;
	int len = 0;
	while ((n=read(sock, response+len, MAX_RESPONSE - len))>0) {
		len += n;
	}
	response[len]=0;

	printf("response:\n%s\n", response);

	close(sock);

	return 1;
}
	
void
printUsage()
{
	printf("Usage: test-talk-server host port user password\n");
	exit(1);
}
////////////////////////////////////////////////////////////////////////

void update_list_rooms() {
    GtkTreeIter iter;
    int i;

    /* Add some messages to the window */
  /*  for (i = 0; i < 10; i++) {
        gchar *msg = g_strdup_printf ("Room %d", i);
        gtk_list_store_append (GTK_LIST_STORE (list_rooms), &iter);
        gtk_list_store_set (GTK_LIST_STORE (list_rooms),&iter,0, msg,-1);
	g_free (msg);
    }*/

    gchar *msg = "Lobby";
    gtk_list_store_append(GTK_LIST_STORE(list_rooms), &iter);
    gtk_list_store_set(GTK_LIST_STORE(list_rooms),&iter,0,msg,-1);
    
}

void update_user_list(){
  char * c = "GET-USERS-IN-ROOM ";
  char r[1000];
  strcpy(r,c);
  strcat(r,user);
  strcat(r," ");
  strcat(r,password);
  strcat(r," ");
  strcat(r,curroom);
  strcat(r,"\r\n");
  sendCommand(host,port,r,response);
  printf("BBBBBB: %s\n",response);
  GtkTreeIter iter;
  int i, j, coun;
  for(i=0; response[i]!='\0';i++){
    }
    gchar * msg = (gchar*)user;
    gtk_list_store_append(GTK_LIST_STORE(user_list),&iter);
    gtk_list_store_set(GTK_LIST_STORE(user_list), &iter, 0, msg,-1);
  //  g_free(msg);
}


/* Create the list of "messages" */
static GtkWidget *create_list( const char * titleColumn, GtkListStore *model )
{
    GtkWidget *scrolled_window;
    GtkWidget *tree_view;
    //GtkListStore *model;
    GtkCellRenderer *cell;
    GtkTreeViewColumn *column;

    int i;
   
    /* Create a new scrolled window, with scrollbars only if needed */
    scrolled_window = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
				    GTK_POLICY_AUTOMATIC, 
				    GTK_POLICY_AUTOMATIC);
   
    //model = gtk_list_store_new (1, G_TYPE_STRING);
    tree_view = gtk_tree_view_new ();
    gtk_container_add (GTK_CONTAINER (scrolled_window), tree_view);
    gtk_tree_view_set_model (GTK_TREE_VIEW (tree_view), GTK_TREE_MODEL (model));
    gtk_widget_show (tree_view);
   
    cell = gtk_cell_renderer_text_new ();

    column = gtk_tree_view_column_new_with_attributes (titleColumn,
                                                       cell,
                                                       "text", 0,
                                                       NULL);
  
    gtk_tree_view_append_column (GTK_TREE_VIEW (tree_view),
	  		         GTK_TREE_VIEW_COLUMN (column));

    return scrolled_window;
}
//send
GtkWidget * child;
static void sendm(){
 GtkTextBuffer * buff = gtk_text_view_get_buffer(GTK_TEXT_VIEW(child));
 //
 GtkTextIter start, end;
 gtk_text_buffer_get_bounds(buff, &start, &end);
 char * text = (char*)gtk_text_buffer_get_text(buff,&start,&end,FALSE);
 printf("%s\r\n",text);
 char * argu = "SEND-MESSAGE ";
 char rr[1000];
 strcpy(rr, argu);
 strcat(rr,user);
 strcat(rr," ");
 strcat(rr,password);
 strcat(rr," ");
 strcat(rr,curroom);
 strcat(rr," ");
 strcat(rr, text);
 strcat(rr,"\r\n");
 sendCommand(host,port,rr,response);
 printf("%s",response);
 gtk_text_buffer_set_text(buff, "", -1); 
}


/* Add some text to our text widget - this is a callback that is invoked
when our window is realized. We could also force our window to be
realized with gtk_widget_realize, but it would have to be part of
a hierarchy first */

static void insert_text( GtkTextBuffer *buffer, const char * initialText )
{
   GtkTextIter iter;
 
   gtk_text_buffer_get_iter_at_offset (buffer, &iter, 0);
   gtk_text_buffer_insert (buffer, &iter, initialText,-1);
}
   
/* Create a scrolled text area that displays a "message" */
/////
//GtkWidget * child;
static GtkWidget *create_text( const char * initialText, int lock )
{
   GtkWidget *scrolled_window;
   GtkWidget *view;
   GtkTextBuffer *buffer;

   view = gtk_text_view_new ();
   buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));

   scrolled_window = gtk_scrolled_window_new (NULL, NULL);
   gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window),
		   	           GTK_POLICY_AUTOMATIC,
				   GTK_POLICY_AUTOMATIC);
  //editable?
  if(lock){
   gtk_text_view_set_editable(GTK_TEXT_VIEW(view), false); 
  }
  //1
   gtk_container_add (GTK_CONTAINER (scrolled_window), view);
   insert_text (buffer, initialText);
   child  = gtk_bin_get_child(GTK_BIN(scrolled_window));
   gtk_widget_show_all (scrolled_window);
   //
   return scrolled_window;
}
GtkWidget *userin;
GtkWidget *passin;
GtkWidget * newWin;
GtkWidget *nWR;
GtkWidget *roomin;
void confirmmr(){

  char * newr = (char*) gtk_entry_get_text(GTK_ENTRY(roomin));
  char * clr = "CREATE-ROOM ";
  char rr[1000];
  strcpy(rr,clr);
  strcat(rr,user);
  
  strcat(rr," ");
  strcat(rr,password);
  strcat(rr," ");
strcat(rr,newr);
strcat(rr,"\r\n");
  sendCommand(host,port,rr,response);
  gtk_widget_hide(nWR);

}

void confirmm(){
//GtkTextBuffer *ub = gtk_entry_get_buffer(GTK_ENTRY(userin));
//GtkTextBuffer *pb = gtk_entry_get_buffer(GTK_ENTRY(passin));
  char * ut = (char*) gtk_entry_get_text(GTK_ENTRY(userin));

  char * pt = (char*) gtk_entry_get_text(GTK_ENTRY(passin));
  printf("%s\n%s\r\n",ut,pt);
  char * clr = "ADD-USER ";
  char rr[1000];
  strcpy(rr,clr);
  strcat(rr,ut);
  
  strcat(rr," ");
  strcat(rr,pt);
  strcat(rr,"\r\n");
  sendCommand(host,port,rr,response);
  gtk_widget_hide(newWin);

}
void createroom(){
  
  nWR = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(nWR), "Create Room");
  gtk_container_set_border_width(GTK_CONTAINER(nWR), 10);
  gtk_widget_set_size_request(GTK_WIDGET(nWR),200,200);
//  gtk_widget_show(newWin);
  GtkWidget *tab = gtk_table_new (5, 6, TRUE);
  gtk_container_add(GTK_CONTAINER(nWR),tab);
  gtk_table_set_row_spacings(GTK_TABLE(tab),5);
  gtk_table_set_col_spacings(GTK_TABLE(tab),5);
//  gtk_widget_show(table);
//  GtkWidget *userin;
//  GtkWidget *passin;
  GtkWidget *confirm = gtk_button_new_with_label("Confirm");
  gtk_table_attach_defaults(GTK_TABLE(tab), confirm, 1,5,5,6);

  roomin = gtk_entry_new();

  gtk_entry_set_text(GTK_ENTRY(roomin), "--type new room--");


  gtk_table_attach_defaults(GTK_TABLE(tab),roomin,0,6,2,3);
  gtk_widget_show(confirm);
  gtk_widget_show(roomin);
  gtk_widget_show(tab);
  gtk_widget_show(nWR);

 // GtkEntryBuffer *ub;

//  GtkEntryBuffer *pb;
//  ub = gtk_entry_get_buffer(GTK_ENTRY(userin));
//  pb = gtk_entry_get_buffer(GTK_ENTRY(passin));
// userchild = gtk_bin_get_child(GTK_BIN(userin));
// passchild = gtk_bin_get_child(GTK_BIN(passin));
  g_signal_connect(confirm,"clicked",G_CALLBACK(confirmmr),NULL);
 // g_signal_connect(confirm("clicked",G_CALLBACK(gtk_widget_hide),NULL)
}

void create(){
  
  newWin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(newWin), "Create Account");
  gtk_container_set_border_width(GTK_CONTAINER(newWin), 10);
  gtk_widget_set_size_request(GTK_WIDGET(newWin),200,200);
//  gtk_widget_show(newWin);
  GtkWidget *tab = gtk_table_new (5, 6, TRUE);
  gtk_container_add(GTK_CONTAINER(newWin),tab);
  gtk_table_set_row_spacings(GTK_TABLE(tab),5);
  gtk_table_set_col_spacings(GTK_TABLE(tab),5);
//  gtk_widget_show(table);
//  GtkWidget *userin;
//  GtkWidget *passin;
  GtkWidget *confirm = gtk_button_new_with_label("Confirm");
  gtk_table_attach_defaults(GTK_TABLE(tab), confirm, 1,5,5,6);

  userin = gtk_entry_new();
  passin = gtk_entry_new();
  gtk_entry_set_text(GTK_ENTRY(userin), "--type user--");
  gtk_entry_set_text(GTK_ENTRY(passin), "--type password--");
  gtk_table_attach_defaults(GTK_TABLE(tab), userin,0,6, 1, 2);
  gtk_table_attach_defaults(GTK_TABLE(tab), passin, 0, 6, 3,4);
  gtk_widget_show(confirm);
  gtk_widget_show(userin);
  gtk_widget_show(passin);
  gtk_widget_show(tab);
  gtk_widget_show(newWin);

 // GtkEntryBuffer *ub;

//  GtkEntryBuffer *pb;
//  ub = gtk_entry_get_buffer(GTK_ENTRY(userin));
//  pb = gtk_entry_get_buffer(GTK_ENTRY(passin));
// userchild = gtk_bin_get_child(GTK_BIN(userin));
// passchild = gtk_bin_get_child(GTK_BIN(passin));
  g_signal_connect(confirm,"clicked",G_CALLBACK(confirmm),NULL);
 // g_signal_connect(confirm("clicked",G_CALLBACK(gtk_widget_hide),NULL)
}


int main( int   argc,
          char *argv[] )
{

	char * command;
	
	if (argc < 5) {
		printUsage();
	}

	host = argv[1];
	sport = argv[2];
        user = argv[3];
	password = argv[4];

	sscanf(sport, "%d", &port);
	char * clr = "CREATE-ROOM ";
	char result[1000];
	strcpy(result,clr);
	
        strcat(result, user);
	strcat(result," ");
	strcat(result, password);
	strcat(result, " ");
        strcat(result, "Lobby\r\n");
	sendCommand(host,port,result,response);	
	if(response[0]!='O'){exit(1);}
   printf("RR: %s\n",response);
	clr = "ENTER-ROOM ";
	char rr[1000];
	strcpy(rr,clr);
	strcat(rr,user);
	strcat(rr," ");
	strcat(rr,password);
	strcat(rr," ");
	strcat(rr, "Lobby\r\n");
	sendCommand(host,port,rr,response);
        curroom = "Lobby";	
	char response[MAX_RESPONSE];
	
    GtkWidget *window;
    GtkWidget *list;
    GtkWidget *usli;
    GtkWidget *messages;
    GtkWidget *myMessage;

    gtk_init (&argc, &argv);
   
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Server");
    g_signal_connect (window, "destroy",
	              G_CALLBACK (gtk_main_quit), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    gtk_widget_set_size_request (GTK_WIDGET (window), 550, 500);

    // Create a table to place the widgets. Use a 7x4 Grid (7 rows x 4 columns)
    GtkWidget *table = gtk_table_new (7, 4, TRUE);
    gtk_container_add (GTK_CONTAINER (window), table);
    gtk_table_set_row_spacings(GTK_TABLE (table), 5);
    gtk_table_set_col_spacings(GTK_TABLE (table), 5);
    gtk_widget_show (table);

    // Add list of rooms. Use columns 0 to 4 (exclusive) and rows 0 to 4 (exclusive)
    list_rooms = gtk_list_store_new (1, G_TYPE_STRING);
    update_list_rooms();
    list = create_list ("Rooms", list_rooms);
    gtk_table_attach_defaults (GTK_TABLE (table), list, 2, 4, 0, 2);
    gtk_widget_show (list);
   
    //USER LIST
    user_list = gtk_list_store_new(1,G_TYPE_STRING);
    update_user_list();
    usli = create_list("Users", user_list);
    gtk_table_attach_defaults(GTK_TABLE(table),usli,0,2,0,2);
    gtk_widget_show(usli);

    // Add messages text. Use columns 0 to 4 (exclusive) and rows 4 to 7 (exclusive) 
    messages = create_text ("---MESSAGE BOARD---\r\n", 1);
    gtk_table_attach_defaults (GTK_TABLE (table), messages, 0, 4, 2, 6);
    
    gtk_widget_show (messages);
    // Add messages text. Use columns 0 to 4 (exclusive) and rows 4 to 7 (exclusive) 

    myMessage = create_text ("--type here--\r\n", 0);
    gtk_table_attach_defaults (GTK_TABLE (table), myMessage, 0, 4, 6, 7);
    gtk_widget_show (myMessage);

    // Add send button. Use columns 0 to 1 (exclusive) and rows 4 to 7 (exclusive)
    GtkWidget *send_button = gtk_button_new_with_label ("Send");
    gtk_table_attach_defaults(GTK_TABLE (table), send_button, 0, 2, 7, 8); 
   gtk_widget_show (send_button);
    //click click
    g_signal_connect(send_button, "clicked", G_CALLBACK(sendm), NULL); 
    //
    //
    /// create, my stuff
    GtkWidget * sign_button = gtk_button_new_with_label("Create Acc.");
    gtk_table_attach_defaults(GTK_TABLE(table),sign_button,2,3,7,8);
    gtk_widget_show(sign_button);
    g_signal_connect(sign_button,"clicked",G_CALLBACK(create),NULL);

    GtkWidget * cr_button = gtk_button_new_with_label("Create Room");
    gtk_table_attach_defaults(GTK_TABLE(table),cr_button,3,4,7,8);
    
    gtk_widget_show(cr_button);
    g_signal_connect(cr_button,"clicked",G_CALLBACK(createroom),NULL);
    //
    //// log in stuff
//    GtkWidget * log_button = gtk_button_new_with_label("Log In");
//    gtk_table_attach_defaults(GTK_TABLE(table),log_button,0,1,7,8);
//    gtk_widget_show(log_button);
//    g_signal_connect(log_button,"clicked",G_CALLBACK(login),NULL);

    ///
    gtk_widget_show (table);
    gtk_widget_show (window);

    gtk_main ();

    return 0;
}

