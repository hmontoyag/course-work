import * as io from 'socket.io-client';
import 'materialize-css/dist/css/materialize.css';
let socket = io();
let containerDiv = <HTMLElement>document.getElementById('container');
let usernameBtn = <HTMLElement>document.getElementById('usernameBtn');
let usernameInput = <HTMLInputElement> document.getElementById('username');
let messageInput = <HTMLInputElement>document.getElementById('message');
let messageBtn = <HTMLElement>document.getElementById('sendMessageBtn');
let collection = <HTMLElement>document.getElementById('message-list');
let id:String;

interface MSG{

    id: String;
    message: String;
}
class Chat {
    currentID:String;
    constructor() {
        this.currentID = socket.id;
        this.checkForMessages();
        this.checkForUsers();
    }
    sendMessage(message:String) {
        if(message) {
            socket.emit('chat message', message);
            this.createNewMessage({id, message});
        }
    }
    checkForMessages() {
        socket.on('chat message', (msg:MSG) => {
            this.createNewMessage(msg);
        });
    }
    createNewMessage(msg:MSG) {
        let div = <HTMLDivElement> document.createElement('div');
        div.classList.add('card');
        div.classList.add('hoverable');
        let div2 = <HTMLDivElement>document.createElement('div');
        div2.classList.add('card-content');
        let spanTitle = <HTMLSpanElement>document.createElement('span');
        spanTitle.classList.add('card-title');
        spanTitle.innerHTML = `${msg.id} - ${msg.message}`;
        if (id && msg.id === id) {
            div.classList.add('blue-grey');
            div.classList.add('darken-1');
            div2.classList.add('white-text');
        }
        div2.appendChild(spanTitle);
        div.appendChild(div2);
        collection.appendChild(div);
    }
    checkForUsers() {
        socket.on('user joined', (username:String) => {
            this.createNewMessage({id: username, message: `just joined`});
        })
    }
    
}

socket.on('connect', () => {
    socket.on('username set', (myId:String) => {
        id = myId;
        containerDiv.style.visibility = 'visible';
    });
    let chat:Chat = new Chat();
    usernameBtn.onclick = () => {
        let username:String = usernameInput.value;
        if(username) {
            socket.emit('set username', username);
        }
    }
    messageBtn.onclick = () => {
        if(id) {
            let message:String = messageInput.value;
            chat.sendMessage(message);
        }
        
    }
})

