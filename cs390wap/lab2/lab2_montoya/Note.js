class Note {
    constructor(name, description, id){
        this.name = name;
        this.description = description;
        this.id = id;
    }
}


class NoteComponent{
    constructor(list, query){
        this.list = list;
        this.query = query;
    }

    filterList(list, query){
        if(query===''){
            return;
        } else {
            let i;
            console.log("EARCH FOR:" + query);
            document.getElementById("noteList").innerHTML = '';
            for (i=0;i!=list.length;i++){
                let name = list[i].name;
                let id = list[i].id;
                let uName = name.toUpperCase();
                
                console.log(uName.indexOf(query));
                if(uName.indexOf(query)!==-1){
                    document.getElementById("noteList").innerHTML += ('<li class="list-group-item"><p><button type="button" class="btn btn-danger" onclick="deleteNote('+id+')" > X </button><button class="btn btn-primary" onclick="selectNote('+id+')" >select</button> '+name+'</p></li>');
                }
        
            }            
       }
    }
}


function resetList(){
    document.getElementById("searchBar").value = '';
    drawList();

}

let countNoName = 0;
let noteList = [];
let intent =0;

function clearBox(){
    document.getElementById("note_content").value = '';
   
}

function saveBox(){
    
    let name = document.getElementById("note_name").value;
    let description = document.getElementById("note_content").value;
    if (name===''){
        document.getElementById("note_name").value = "New Note " + countNoName + "!";
        name = document.getElementById("note_name").value;
        countNoName++;
    }
    
    let n = new Note(name,description,intent);
    //console.log("SAVING: " + n.name + " / " + n.id);
    
   
    document.getElementById("note_name").value = '';
    document.getElementById("note_content").value = '';
    document.getElementById("searchInput").value = '';
    noteList.push(n);
    intent++;
    drawList();

}

function deleteNote(id){
    let i;
    for(i=0;i!=noteList.length;i++){
        if(id===noteList[i].id){
            noteList.splice(i,1);
            break;
        }
    }
    drawList();
    document.getElementById("searchInput").value = '';
    console.log("DELETE");
}

function selectNote(id){
    let i;
    for(i=0;i!=noteList.length;i++){
        if(id===noteList[i].id){
            let name = noteList[i].name;
            let description = noteList[i].description;
            document.getElementById("note_name").value = name;
            document.getElementById("note_content").value = description;
            break;
        }
    }
}

function drawList(){
    document.getElementById("noteList").innerHTML = '';
    let i;
    for (i=0;i!=noteList.length;i++){
        let name = noteList[i].name;
        let id = noteList[i].id;
        //console.log("printName: " + name);
        //console.log("printID: " + id);
        document.getElementById("noteList").innerHTML += ('<li class="list-group-item"><p><button type="button" class="btn btn-danger" onclick="deleteNote('+id+')" > X </button><button class="btn btn-primary" onclick="selectNote('+id+')" >select</button> '+name+'</p></li>');

    }
}

function filter() {
    // Declare variables
    let input, filter, ul, li, a, i;
    input = document.getElementById("searchInput").value;
    filter = input.toUpperCase();
    let nc = new NoteComponent(noteList, filter);
    nc.filterList(noteList,filter);
}