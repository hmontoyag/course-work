const express = require('express');
const bodyParser = require('body-parser');

const app = express();
app.use(bodyParser.urlencoded({ extended: true}));
app.use(bodyParser.json());

let itemList = [];
let token = ".";
let item_id=0;
app.get('/', (req, res) => {
    app.use(express.static('./src'));
    res.sendFile('index.html',{root:'src'});
    
});
app.get('/items', (req, res) => {
    
    //console.log(token);
    
        if(token.length===20){
            res.send(itemList)
        } else {
           
            res.send(null);
        }  
    
});
app.get('/items/search?search=:search&price=:price&rating=:rating', (req, res) => {
    if(token.length===20){ 
    let search = req.query.search;
    let range = req.query.price;
    let rating = req.query.rating;
    console.log(search);
    console.log(range);
    console.log(rating);
    }else{
        res.status(400).send({ message: 'Not logged in. Faile to auth.', status: '400'});
            
    }
});
app.get('/items/:id/', (req, res) => {
    
    //console.log(token);
    let id = req.params.id;
    //console.log("ID = " + id);
        if(token.length===20){
            let exist = 0;
            let index;
            if(!itemList[id]){
                res.status(400).send({ message: 'no item', status: '400'});
            }else{
                
                res.send(itemList[id]);
            } 
        } else {
            //console.log("ENDO");
            //console.log(req.get("authorization"));
            res.status(400).send({ message: 'Not logged in. Faile to auth.', status: '400'});
            
        }  
    
});

app.get('/item-detail/:id', (req, res) => {
    app.use(express.static('./src/item-detail'));
    res.sendFile('item-detail.html',{root:'src/item-detail'});
    
});

app.get('/login', (req, res) => {
    app.use(express.static('./src/login'));
    res.sendFile('login.html',{root:'src/login'});
});
app.post('/login', (req, res) => {
    let username = req.body.username;
    let password = req.body.password;
//console.log(username + " - " + password);
    /*neither of the fields could end null if sent through frontend
    if(password === null){
        res.status(400).send({ message: 'password null', status: '400'});
    }*/
    /*if(username === null){
        res.status(400).send({ message: 'username null', status: '400'});
    }*/
    if(username.length === 0){
        res.status(400).send({ message: 'Authentication unsuccessful, username is empty', status: '400'});
    }
    if(username.length < 8){
        res.status(400).send({ message: 'Authentication unsuccessful, username too short', status: '400'});
    }
    if(username.length > 16){
        res.status(400).send({ message: 'Authentication unsuccessful, username too long', status: '400'});
    }
    if(password.length > 16){
        res.status(400).send({ message: 'Authentication unsuccessful, password too long', status: '400'});
    }
    if(password.length === 0){
        res.status(400).send({ message: 'Authentication unsuccessful, password is empty', status: '400'});
    }
    if(password.length < 8){
        res.status(400).send({ message: 'Authentication unsuccessful, password too short', status: '400'});
    }
    if(username === 'cs390wap' && password === 'cs390wap') {
        token = Math.random().toString(36).substring(2);
        token = token + Math.random().toString(36).substring(2);
        token = token + Math.random().toString(36).substring(2);
        token = token.substr(0,20)
        //console.log(token.length);
        res.setHeader("Set-Authorization",token);
        res.status(200).send({ message: 'Authentication successful', status: '200', idtoken: token});
    }else{
        res.status(600).send({ message: 'Authentication unsuccessful, wrong username or password ', status: '600'});
    }
});
app.get('/new-item/new-item.html', (req, res) => {

    app.use(express.static('./src'));
    res.sendFile('new-item.html',{root:'src/new-item'});
});
app.post('/new-item', (req, res) => {
    if(token.length===20){
        let tname = req.body.name;
        let tdescription = req.body.description;
        let tprice = req.body.price;
        let trating = req.body.rating;
        let repeat = 0;
        if(tname.length===0 ||tdescription.length===0 ||tprice.length===0 ||trating.length===0 ||tprice < 0.1||trating>5||trating<1){
            res.status(400).send({ message: 'Bad Entry. Fill all and make sure price>0.1, and rating between 1-5', status: '400'});
        }
        for (let i =0; i!=itemList.length;i++){
            if(itemList[i].name===tname){
                repeat = -1;
            }
        }
        if(repeat === -1){
            res.status(400).send({ message: 'Duplicate entry', status: '400'});
        } else {
            let item={name: tname,description:tdescription,price:tprice,rating:trating,id:item_id};
            item_id++;
            itemList.push(item);

            res.status(200).send({ message: 'Add', status: '200',item_added:item });
        }
    } else {
        //console.log("ENDO");
        //console.log(req.get("authorization"));
        res.status(400).send({ message: 'Not logged in. Faile to auth.', status: '400'});
    }  
});



/*app.get('/*.*', (req, res) => {
    app.use(express.static('./src/public'));
    res.sendFile('index.html',{root:'src/public'});
           
});*/







app.listen(8650, () => console.log(`I'm listening on port 8650`));