#include <yahoo2.h>
#include <yahoo2_callbacks.h>


#include <stdio.h>
#include <stdarg.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h> /* close */

#include <event.h>


/*
 * Name: ext_yahoo_got_ignore
 * 	Called when the ignore list is got from the server
 * Params:
 * 	id   - the id that identifies the server connection
 * 	igns - the ignore list
 */
void ext_yahoo_got_ignore(int id, YList * igns) {

}





/*
 * Name: ext_yahoo_got_identities
 * 	Called when the contact list is got from the server
 * Params:
 * 	id   - the id that identifies the server connection
 * 	ids  - the identity list
 */
void ext_yahoo_got_identities(int id, YList * ids) {

}





/*
 * Name: ext_yahoo_got_cookies
 * 	Called when the cookie list is got from the server
 * Params:
 * 	id   - the id that identifies the server connection
 */
void ext_yahoo_got_cookies(int id) {

}




/*
 * Name: ext_yahoo_status_changed
 * 	Called when remote user's status changes.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	who  - the handle of the remote user
 * 	stat - status code (enum yahoo_status)
 * 	msg  - the message if stat == YAHOO_STATUS_CUSTOM
 * 	away - whether the contact is away or not (YAHOO_STATUS_CUSTOM)
 * 	       for YAHOO_STATUS_IDLE, this is the number of seconds he is idle
 */
void ext_yahoo_status_changed(int id, char *who, int stat, char *msg, int away) {

}




/*
 * Name: ext_yahoo_got_im
 * 	Called when remote user sends you a message.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	who  - the handle of the remote user
 * 	msg  - the message - NULL if stat == 2
 * 	tm   - timestamp of message if offline
 * 	stat - message status - 0
 * 				1
 * 				2 == error sending message
 * 				5
 * 	utf8 - whether the message is encoded as utf8 or not
 */
void ext_yahoo_got_im(int id, char *who, char *msg, long tm, int stat, int utf8) {

}




/*
 * Name: ext_yahoo_got_conf_invite
 * 	Called when remote user sends you a conference invitation.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	who  - the user inviting you
 * 	room - the room to join
 * 	msg  - the message
 *	members - the initial members of the conference (null terminated list)
 */
void ext_yahoo_got_conf_invite(int id, char *who, char *room, char *msg, YList *members) {

}




/*
 * Name: ext_yahoo_conf_userdecline
 * 	Called when someone declines to join the conference.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	who  - the user who has declined
 * 	room - the room
 * 	msg  - the declining message
 */
void ext_yahoo_conf_userdecline(int id, char *who, char *room, char *msg) {

}




/*
 * Name: ext_yahoo_conf_userjoin
 * 	Called when someone joins the conference.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	who  - the user who has joined
 * 	room - the room joined
 */
void ext_yahoo_conf_userjoin(int id, char *who, char *room) {

}




/*
 * Name: ext_yahoo_conf_userleave
 * 	Called when someone leaves the conference.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	who  - the user who has left
 * 	room - the room left
 */
void ext_yahoo_conf_userleave(int id, char *who, char *room) {

}






/*
 * Name: ext_yahoo_chat_cat_xml
 * 	Called when joining the chatroom.
 * Params:
 * 	id      - the id that identifies the server connection
 * 	room    - the room joined, used in all other chat calls, freed by 
 * 	          library after call
 * 	topic   - the topic of the room, freed by library after call
 *	members - the initial members of the chatroom (null terminated YList of 
 *	          yahoo_chat_member's) Must be freed by the client
 */
void ext_yahoo_chat_cat_xml(int id, char *xml) {

}


/*
 * Name: ext_yahoo_chat_join
 * 	Called when joining the chatroom.
 * Params:
 * 	id      - the id that identifies the server connection
 * 	room    - the room joined, used in all other chat calls, freed by 
 * 	          library after call
 * 	topic   - the topic of the room, freed by library after call
 *	members - the initial members of the chatroom (null terminated YList 
 *	          of yahoo_chat_member's) Must be freed by the client
 *	fd	- the socket where the connection is coming from (for tracking)
 */
void ext_yahoo_chat_join(int id, char *room, char *topic, YList *members, int fd) {

}






/*
 * Name: ext_yahoo_chat_userjoin
 * 	Called when someone joins the chatroom.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	room - the room joined
 * 	who  - the user who has joined, Must be freed by the client
 */
void ext_yahoo_chat_userjoin(int id, char *room, struct yahoo_chat_member *who) {

}




/*
 * Name: ext_yahoo_chat_userleave
 * 	Called when someone leaves the chatroom.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	room - the room left
 * 	who  - the user who has left (Just the User ID)
 */
void ext_yahoo_chat_userleave(int id, char *room, char *who) {

}




/*
 * Name: ext_yahoo_chat_message
 * 	Called when someone messages in the chatroom.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	room - the room
 * 	who  - the user who messaged (Just the user id)
 * 	msg  - the message
 * 	msgtype  - 1 = Normal message
 * 		   2 = /me type message
 * 	utf8 - whether the message is utf8 encoded or not
 */
void ext_yahoo_chat_message(int id, char *who, char *room, char *msg, int msgtype, int utf8) {

}

/*
 *
 * Name: ext_yahoo_chat_yahoologout
 *	called when yahoo disconnects your chat session
 *	Note this is called whenver a disconnect happens, client or server
 *	requested. Care should be taken to make sure you know the origin 
 *	of the disconnect request before doing anything here (auto-join's etc)
 * Params:
 *	id   - the id that identifies this connection
 * Returns:
 *	nothing.
 */
void ext_yahoo_chat_yahoologout(int id) {

}

/*
 *
 * Name: ext_yahoo_chat_yahooerror
 *	called when yahoo sends back an error to you
 *	Note this is called whenver chat message is sent into a room
 *	in error (fd not connected, room doesn't exists etc)
 *	Care should be taken to make sure you know the origin 
 *	of the error before doing anything about it.
 * Params:
 *	id   - the id that identifies this connection
 * Returns:
 *	nothing.
 */

void ext_yahoo_chat_yahooerror(int id) {

}

/*
 * Name: ext_yahoo_conf_message
 * 	Called when someone messages in the conference.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	who  - the user who messaged
 * 	room - the room
 * 	msg  - the message
 * 	utf8 - whether the message is utf8 encoded or not
 */
void ext_yahoo_conf_message(int id, char *who, char *room, char *msg, int utf8) {

}




/*
 * Name: ext_yahoo_got_file
 * 	Called when someone sends you a file
 * Params:
 * 	id   - the id that identifies the server connection
 * 	who  - the user who sent the file
 * 	url  - the file url
 * 	expires  - the expiry date of the file on the server (timestamp)
 * 	msg  - the message
 * 	fname- the file name if direct transfer
 * 	fsize- the file size if direct transfer
 */
void ext_yahoo_got_file(int id, char *who, char *url, long expires, char *msg, char *fname, unsigned long fesize) {

}




/*
 * Name: ext_yahoo_contact_added
 * 	Called when a contact is added to your list
 * Params:
 * 	id   - the id that identifies the server connection
 * 	myid - the identity he was added to
 * 	who  - who was added
 * 	msg  - any message sent
 */
void ext_yahoo_contact_added(int id, char *myid, char *who, char *msg) {

}




/*
 * Name: ext_yahoo_rejected
 * 	Called when a contact rejects your add
 * Params:
 * 	id   - the id that identifies the server connection
 * 	who  - who rejected you
 * 	msg  - any message sent
 */
void ext_yahoo_rejected(int id, char *who, char *msg) {

}




/*
 * Name: ext_yahoo_typing_notify
 * 	Called when remote user starts or stops typing.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	who  - the handle of the remote user
 * 	stat - 1 if typing, 0 if stopped typing
 */
void ext_yahoo_typing_notify(int id, char *who, int stat) {

}




/*
 * Name: ext_yahoo_game_notify
 * 	Called when remote user starts or stops a game.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	who  - the handle of the remote user
 * 	stat - 1 if game, 0 if stopped gaming
 */
void ext_yahoo_game_notify(int id, char *who, int stat) {

}




/*
 * Name: ext_yahoo_mail_notify
 * 	Called when you receive mail, or with number of messages
 * Params:
 * 	id   - the id that identifies the server connection
 * 	from - who the mail is from - NULL if only mail count
 * 	subj - the subject of the mail - NULL if only mail count
 * 	cnt  - mail count - 0 if new mail notification
 */
void ext_yahoo_mail_notify(int id, char *from, char *subj, int cnt) {

}




/*
 * Name: ext_yahoo_system_message
 * 	System message
 * Params:
 * 	id   - the id that identifies the server connection
 * 	msg  - the message
 */
void ext_yahoo_system_message(int id, char *msg) {

}

/*
 * Name: ext_yahoo_got_webcam_image
 * 	Called when you get a webcam update
 *	An update can either be receiving an image, a part of an image or
 *	just an update with a timestamp
 * Params:
 * 	id         - the id that identifies the server connection
 * 	who        - the user who's webcam we're viewing
 *	image      - image data
 *	image_size - length of the image in bytes
 *	real_size  - actual length of image data
 *	timestamp  - milliseconds since the webcam started
 *
 *	If the real_size is smaller then the image_size then only part of
 *	the image has been read. This function will keep being called till
 *	the total amount of bytes in image_size has been read. The image
 *	received is in JPEG-2000 Code Stream Syntax (ISO/IEC 15444-1).
 *	The size of the image will be either 160x120 or 320x240.
 *	Each webcam image contains a timestamp. This timestamp should be
 *	used to keep the image in sync since some images can take longer
 *	to transport then others. When image_size is 0 we can still receive
 *	a timestamp to stay in sync
 */
void ext_yahoo_got_webcam_image(int id, const char * who,
		const unsigned char *image, unsigned int image_size, unsigned int real_size,
				unsigned int timestamp) {

}




/*
 * Name: ext_yahoo_webcam_invite
 * 	Called when you get a webcam invitation
 * Params:
 * 	id   - the id that identifies the server connection
 * 	from - who the invitation is from
 */
void ext_yahoo_webcam_invite(int id, char *from) {

}




/*
 * Name: ext_yahoo_webcam_invite_reply
 * 	Called when you get a response to a webcam invitation
 * Params:
 * 	id   - the id that identifies the server connection
 * 	from - who the invitation response is from
 *	accept - 0 (decline), 1 (accept)
 */
void ext_yahoo_webcam_invite_reply(int id, char *from, int accept) {

}



/*
 * Name: ext_yahoo_webcam_closed
 * 	Called when the webcam connection closed
 * Params:
 * 	id   - the id that identifies the server connection
 * 	who  - the user who we where connected to
 *	reason - reason why the connection closed
 *	         1 = user stopped broadcasting
 *	         2 = user cancelled viewing permission
 *	         3 = user declines permission
 *	         4 = user does not have webcam online
 */
void ext_yahoo_webcam_closed(int id, char *who, int reason) {

}


/*
 * Name: ext_yahoo_got_search_result
 *      Called when the search result received from server
 * Params:
 *      id  	 - the id that identifies the server connection
 * 	found	 - total number of results returned in the current result set
 * 	start	 - offset from where the current result set starts
 * 	total	 - total number of results available (start + found <= total)
 * 	contacts - the list of results as a YList of yahoo_found_contact
 * 		   these will be freed after this function returns, so
 * 		   if you need to use the information, make a copy
 */
void ext_yahoo_got_search_result(int id, int found, int start, int total, YList *contacts) {

}



/*
 * Name: ext_yahoo_error
 * 	Called on error.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	err  - the error message
 * 	fatal- whether this error is fatal to the connection or not
 */
void ext_yahoo_error(int id, char *err, int fatal) {

}




/*
 * Name: ext_yahoo_webcam_viewer
 *	Called when a viewer disconnects/connects/requests to connect
 * Params:
 *	id  - the id that identifies the server connection
 *	who - the viewer
 *	connect - 0=disconnect 1=connect 2=request
 */
void ext_yahoo_webcam_viewer(int id, char *who, int connect) {

}




/*
 * Name: ext_yahoo_webcam_data_request
 *	Called when you get a request for webcam images
 * Params:
 *	id   - the id that identifies the server connection
 *	send - whether to send images or not
 */
void ext_yahoo_webcam_data_request(int id, int send) {

}




/*
 * Name: ext_yahoo_log
 * 	Called to log a message.
 * Params:
 * 	fmt  - the printf formatted message
 * Returns:
 * 	0
 */
int ext_yahoo_log(char *fmt, ...) {
  /* for now, just hack this bit; a real wrapper needs to pass this to the script layer */
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  return 0;
}

/*
 * Name: ext_yahoo_add_handler
 * 	Add a listener for the fd.  Must call yahoo_read_ready
 * 	when a YAHOO_INPUT_READ fd is ready and yahoo_write_ready
 * 	when a YAHOO_INPUT_WRITE fd is ready.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	fd   - the fd on which to listen
 * 	cond - the condition on which to call the callback
 * 	data - callback data to pass to yahoo_*_ready
 * 	
 * Returns: a tag to be used when removing the handler
 */
int ext_yahoo_add_handler(int id, int fd, yahoo_input_condition cond, void *data) {
  return -1;
}

/*
 * Name: ext_yahoo_remove_handler
 * 	Remove the listener for the fd.
 * Params:
 * 	id   - the id that identifies the connection
 * 	tag  - the handler tag to remove
 */
void ext_yahoo_remove_handler(int id, int tag) {
  
}

/*
 * Name: ext_yahoo_connect
 * 	Connect to a host:port
 * Params:
 * 	host - the host to connect to
 * 	port - the port to connect on
 * Returns:
 * 	a unix file descriptor to the socket
 */
int ext_yahoo_connect(char *host, int port) {
  /* should hand this off to the scripting code, but blah */
  int sd;
  struct sockaddr_in local, server;
  struct hostent *h;
  
  h = gethostbyname(host);
  if(h==NULL) {
    return -1;
  }

  server.sin_family = h->h_addrtype;
  memcpy((char *) &server.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
  server.sin_port = htons(port);

  /* create socket */
  sd = socket(AF_INET, SOCK_STREAM, 0);
  if(sd<0) {
    return -1;
  }

  /* bind any port number */
  local.sin_family = AF_INET;
  local.sin_addr.s_addr = htonl(INADDR_ANY);
  local.sin_port = htons(0);
  
  if(bind(sd, (struct sockaddr *) &local, sizeof(local)) < 0) {
    return -1;
  }
				
  /* connect to server */
  if(connect(sd, (struct sockaddr *) &server, sizeof(server)) < 0) {
    return -1;
  }
  printf("connected to %s %d\n", host, port);
  return sd;
}




