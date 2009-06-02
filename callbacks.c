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

#define YAHOO_CALLBACK_TYPE(x) x

/*
 * Name: ext_yahoo_login_response
 * 	Called when the login process is complete
 * Params:
 * 	id   - the id that identifies the server connection
 * 	succ - enum yahoo_login_status
 * 	url  - url to reactivate account if locked
 */
void py_ext_yahoo_login_response(int id, int succ, char *url);
void YAHOO_CALLBACK_TYPE(ext_yahoo_login_response)(int id, int succ, const char *url) {
  py_ext_yahoo_login_response(id, succ, (char *)url);
}


/*
 * Name: ext_yahoo_got_buddies
 * 	Called when the contact list is got from the server
 * Params:
 * 	id   - the id that identifies the server connection
 * 	buds - the buddy list
 */
/* implemented directly in pyrex
void YAHOO_CALLBACK_TYPE(ext_yahoo_got_buddies)(int id, YList * buds) {

}
*/

/*
 * Name: ext_yahoo_got_ignore
 * 	Called when the ignore list is got from the server
 * Params:
 * 	id   - the id that identifies the server connection
 * 	igns - the ignore list
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_got_ignore)(int id, YList * igns) {

}


/*
 * Name: ext_yahoo_got_identities
 * 	Called when the contact list is got from the server
 * Params:
 * 	id   - the id that identifies the server connection
 * 	ids  - the identity list
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_got_identities)(int id, YList * ids) {

}

/*
 * Name: ext_yahoo_got_cookies
 * 	Called when the cookie list is got from the server
 * Params:
 * 	id   - the id that identifies the server connection
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_got_cookies)(int id) {

}


/*
 * Name: ext_yahoo_got_ping
 * 	Called when the ping packet is received from the server
 * Params:
 * 	id   - the id that identifies the server connection
 *  errormsg - optional error message
 */
void py_ext_yahoo_got_ping(int id, char *errormsg);
void YAHOO_CALLBACK_TYPE(ext_yahoo_got_ping)(int id, const char *errormsg) {
  py_ext_yahoo_got_ping(id, errormsg);
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
 * 	idle - this is the number of seconds he is idle [if he is idle]
 *	mobile - this is set for mobile users/buddies
 *	TODO: add support for pager, chat, and game states
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_status_changed)(int id, const char *who, int stat, const char *msg, int away, int idle, int mobile) {

}


/*
 * Name: ext_yahoo_got_im
 * 	Called when remote user sends you a message.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	me   - the identity the message was sent to
 * 	who  - the handle of the remote user
 * 	msg  - the message - NULL if stat == 2
 * 	tm   - timestamp of message if offline
 * 	stat - message status - 0
 * 				1
 * 				2 == error sending message
 * 				5
 * 	utf8 - whether the message is encoded as utf8 or not
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_got_im)(int id, const char *me, const char *who, const char *msg, long tm, int stat, int utf8) {

}


/*
 * Name: ext_yahoo_got_conf_invite
 * 	Called when remote user sends you a conference invitation.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	me   - the identity the invitation was sent to
 * 	who  - the user inviting you
 * 	room - the room to join
 * 	msg  - the message
 *	members - the initial members of the conference (null terminated list)
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_got_conf_invite)(int id, const char *me, const char *who, const char *room, const char *msg, YList *members) {

}

/*
 * Name: ext_yahoo_conf_userdecline
 * 	Called when someone declines to join the conference.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	me   - the identity in the conference
 * 	who  - the user who has declined
 * 	room - the room
 * 	msg  - the declining message
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_conf_userdecline)(int id, const char *me, const char *who, const char *room, const char *msg) {

}


/*
 * Name: ext_yahoo_conf_userjoin
 * 	Called when someone joins the conference.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	me   - the identity in the conference
 * 	who  - the user who has joined
 * 	room - the room joined
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_conf_userjoin)(int id, const char *me, const char *who, const char *room) {

}


/*
 * Name: ext_yahoo_conf_userleave
 * 	Called when someone leaves the conference.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	me   - the identity in the conference
 * 	who  - the user who has left
 * 	room - the room left
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_conf_userleave)(int id, const char *me, const char *who, const char *room) {

}


/*
 * Name: ext_yahoo_chat_cat_xml
 * 	Called when ?
 * Params:
 * 	id      - the id that identifies the server connection
 * 	xml     - ?
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_chat_cat_xml)(int id, const char *xml) {

}


/*
 * Name: ext_yahoo_chat_join
 * 	Called when joining the chatroom.
 * Params:
 * 	id      - the id that identifies the server connection
 * 	me   - the identity in the chatroom
 * 	room    - the room joined, used in all other chat calls, freed by 
 * 	          library after call
 * 	topic   - the topic of the room, freed by library after call
 *	members - the initial members of the chatroom (null terminated YList 
 *	          of yahoo_chat_member's) Must be freed by the client
 *	fd	- the socket where the connection is coming from (for tracking)
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_chat_join)(int id, const char *me, const char *room, const char *topic, YList *members, int fd) {

}


/*
 * Name: ext_yahoo_chat_userjoin
 * 	Called when someone joins the chatroom.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	me   - the identity in the chatroom
 * 	room - the room joined
 * 	who  - the user who has joined, Must be freed by the client
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_chat_userjoin)(int id, const char *me, const char *room, struct yahoo_chat_member *who) {

}


/*
 * Name: ext_yahoo_chat_userleave
 * 	Called when someone leaves the chatroom.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	me   - the identity in the chatroom
 * 	room - the room left
 * 	who  - the user who has left (Just the User ID)
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_chat_userleave)(int id, const char *me, const char *room, const char *who) {

}


/*
 * Name: ext_yahoo_chat_message
 * 	Called when someone messages in the chatroom.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	me   - the identity in the chatroom
 * 	room - the room
 * 	who  - the user who messaged (Just the user id)
 * 	msg  - the message
 * 	msgtype  - 1 = Normal message
 * 		   2 = /me type message
 * 	utf8 - whether the message is utf8 encoded or not
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_chat_message)(int id, const char *me, const char *who, const char *room, const char *msg, int msgtype, int utf8) {

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
 * 	me   - the identity in the chatroom
 * Returns:
 *	nothing.
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_chat_yahoologout)(int id, const char *me) {

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
 * 	me   - the identity in the chatroom
 * Returns:
 *	nothing.
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_chat_yahooerror)(int id, const char *me) {

}


/*
 * Name: ext_yahoo_conf_message
 * 	Called when someone messages in the conference.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	me   - the identity the conf message was sent to
 * 	who  - the user who messaged
 * 	room - the room
 * 	msg  - the message
 * 	utf8 - whether the message is utf8 encoded or not
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_conf_message)(int id, const char *me, const char *who, const char *room, const char *msg, int utf8) {

}


/*
 * Name: ext_yahoo_got_file
 * 	Called when someone sends you a file
 * Params:
 * 	id   - the id that identifies the server connection
 * 	me   - the identity the file was sent to
 * 	who  - the user who sent the file
 * 	url  - the file url
 * 	expires  - the expiry date of the file on the server (timestamp)
 * 	msg  - the message
 * 	fname- the file name if direct transfer
 * 	fsize- the file size if direct transfer
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_got_file)(int id, const char *me, const char *who, const char *url, long expires, const char *msg, const char *fname, unsigned long fesize) {

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
void YAHOO_CALLBACK_TYPE(ext_yahoo_contact_added)(int id, const char *myid, const char *who, const char *msg) {

}


/*
 * Name: ext_yahoo_rejected
 * 	Called when a contact rejects your add
 * Params:
 * 	id   - the id that identifies the server connection
 * 	who  - who rejected you
 * 	msg  - any message sent
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_rejected)(int id, const char *who, const char *msg) {

}


/*
 * Name: ext_yahoo_typing_notify
 * 	Called when remote user starts or stops typing.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	me   - the handle of the identity the notification is sent to
 * 	who  - the handle of the remote user
 * 	stat - 1 if typing, 0 if stopped typing
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_typing_notify)(int id, const char *me, const char *who, int stat) {

}


/*
 * Name: ext_yahoo_game_notify
 * 	Called when remote user starts or stops a game.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	me   - the handle of the identity the notification is sent to
 * 	who  - the handle of the remote user
 * 	stat - 1 if game, 0 if stopped gaming
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_game_notify)(int id, const char *me, const char *who, int stat) {

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
void YAHOO_CALLBACK_TYPE(ext_yahoo_mail_notify)(int id, const char *from, const char *subj, int cnt) {

}


/*
 * Name: ext_yahoo_system_message
 * 	System message
 * Params:
 * 	id   - the id that identifies the server connection
 * 	msg  - the message
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_system_message)(int id, const char *msg) {

}

/*
 * Name: ext_yahoo_got_buddyicon
 * 	Buddy icon received
 * Params:
 * 	id - the id that identifies the server connection
 * 	me - the handle of the identity the notification is sent to
 * 	who - the person the buddy icon is for
 * 	url - the url to use to load the icon
 * 	checksum - the checksum of the icon content
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_got_buddyicon)(int id, const char *me, const char *who, const char *url, int checksum) {
}

/*
 * Name: ext_yahoo_got_buddyicon_checksum
 * 	Buddy icon checksum received
 * Params:
 * 	id - the id that identifies the server connection
 * 	me - the handle of the identity the notification is sent to
 * 	who - the yahoo id of the buddy icon checksum is for
 * 	checksum - the checksum of the icon content
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_got_buddyicon_checksum)(int id, const char *me,const char *who, int checksum) {
}

/*
 * Name: ext_yahoo_got_buddyicon_request
 * 	Buddy icon request received
 * Params:
 * 	id - the id that identifies the server connection
 * 	me - the handle of the identity the notification is sent to
 * 	who - the yahoo id of the buddy that requested the buddy icon
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_got_buddyicon_request)(int id, const char *me, const char *who) {
}

/*
 * Name: ext_yahoo_got_buddyicon_request
 * 	Buddy icon request received
 * Params:
 * 	id - the id that identifies the server connection
 * 	url - remote url, the uploaded buddy icon can be fetched from
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_buddyicon_uploaded)(int id, const char *url) {
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
void YAHOO_CALLBACK_TYPE(ext_yahoo_got_webcam_image)(int id, const char * who,
		const unsigned char *image, unsigned int image_size, unsigned int real_size,
		unsigned int timestamp) {
}


/*
 * Name: ext_yahoo_webcam_invite
 * 	Called when you get a webcam invitation
 * Params:
 * 	id   - the id that identifies the server connection
 * 	me   - identity the invitation is to
 * 	from - who the invitation is from
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_webcam_invite)(int id, const char *me, const char *from) {
}


/*
 * Name: ext_yahoo_webcam_invite_reply
 * 	Called when you get a response to a webcam invitation
 * Params:
 * 	id   - the id that identifies the server connection
 * 	me   - identity the invitation response is to
 * 	from - who the invitation response is from
 *	accept - 0 (decline), 1 (accept)
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_webcam_invite_reply)(int id, const char *me, const char *from, int accept) {
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
void YAHOO_CALLBACK_TYPE(ext_yahoo_webcam_closed)(int id, const char *who, int reason) {
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
void YAHOO_CALLBACK_TYPE(ext_yahoo_got_search_result)(int id, int found, int start, int total, YList *contacts) {
}


/*
 * Name: ext_yahoo_error
 * 	Called on error.
 * Params:
 * 	id   - the id that identifies the server connection
 * 	err  - the error message
 * 	fatal- whether this error is fatal to the connection or not
 * 	num  - Which error is this
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_error)(int id, const char *err, int fatal, int num) {
}


/*
 * Name: ext_yahoo_webcam_viewer
 *	Called when a viewer disconnects/connects/requests to connect
 * Params:
 *	id  - the id that identifies the server connection
 *	who - the viewer
 *	connect - 0=disconnect 1=connect 2=request
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_webcam_viewer)(int id, const char *who, int connect) {
}


/*
 * Name: ext_yahoo_webcam_data_request
 *	Called when you get a request for webcam images
 * Params:
 *	id   - the id that identifies the server connection
 *	send - whether to send images or not
 */
void YAHOO_CALLBACK_TYPE(ext_yahoo_webcam_data_request)(int id, int send) {
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
/* implemented directly in pyrex
int YAHOO_CALLBACK_TYPE(ext_yahoo_add_handler)(int id, int fd, yahoo_input_condition cond, void *data) {
}
*/

/*
 * Name: ext_yahoo_remove_handler
 * 	Remove the listener for the fd.
 * Params:
 * 	id   - the id that identifies the connection
 * 	tag  - the handler tag to remove
 */
/* implemented in pyrex
void YAHOO_CALLBACK_TYPE(ext_yahoo_remove_handler)(int id, int tag) {
}
*/


/*
 * Name: ext_yahoo_connect
 * 	Connect to a host:port
 * Params:
 * 	host - the host to connect to
 * 	port - the port to connect on
 * Returns:
 * 	a unix file descriptor to the socket
 */
int py_ext_yahoo_connect(char *host, int port);
int YAHOO_CALLBACK_TYPE(ext_yahoo_connect)(const char *host, int port) {
  return py_ext_yahoo_connect((char *)host, port);
}


/*
 * Name: ext_yahoo_connect_async
 * 	Connect to a host:port asynchronously.  This function should return
 * 	immediately returing a tag used to identify the connection handler,
 * 	or a pre-connect error (eg: host name lookup failure).
 * 	Once the connect completes (successfully or unsuccessfully), callback
 * 	should be called (see the signature for yahoo_connect_callback).
 * 	The callback may safely be called before this function returns, but
 * 	it should not be called twice.
 * Params:
 * 	id   - the id that identifies this connection
 * 	host - the host to connect to
 * 	port - the port to connect on
 * 	callback - function to call when connect completes
 * 	callback_data - data to pass to the callback function
 * Returns:
 * 	a unix file descriptor to the socket
 */
int py_ext_yahoo_connect_async(int id, char *host, int port, 
			       yahoo_connect_callback callback, void *callback_data);

int YAHOO_CALLBACK_TYPE(ext_yahoo_connect_async)(int id, const char *host, int port, 
		yahoo_connect_callback callback, void *callback_data) {
  return py_ext_yahoo_connect_async(id, (char *)host, port, callback, callback_data);
}


/*
 * Name: ext_yahoo_log
 * 	Called to log a message.
 * Params:
 * 	fmt  - the printf formatted message
 * Returns:
 * 	0
 */
int ext_yahoo_log(const char *fmt, ...) {
  /* for now, just hack this bit; a real wrapper needs to pass this to the script layer */
  va_list args;
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  return 0;
}
