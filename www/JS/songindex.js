const baseURL = window.location.origin + "/";

console.log(baseURL);

var songIndex = [
    {src : baseURL+"Songs/KanyeWest/GoodAssJob/livefastdieyoung.mp3", index : {album : "goodassjob", song : "livefastdieyoung", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/GoodAssJob/mamasboyfriend.mp3", index : {album : "goodassjob", song : "mamasboyfriend", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/GoodAssJob/flashinglights2.mp3", index : {album : "goodassjob", song : "flashinglights2", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/GoodAssJob/eyesclosed.mp3", index : {album : "goodassjob", song : "eyesclosed", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/GoodAssJob/tragicallybeautiful.mp3", index : {album : "goodassjob", song : "tragicallybeautiful", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/GoodAssJob/nopartiesinla.mp3", index : {album : "goodassjob", song : "nopartiesinla", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/GoodAssJob/heartbreaker.mp3", index : {album : "goodassjob", song : "heartbreaker", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/GoodAssJob/dontstop.mp3", index : {album : "goodassjob", song : "dontstop", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/GoodAssJob/shootup.mp3", index : {album : "goodassjob", song : "shootup", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/GoodAssJob/icecube.mp3", index : {album : "goodassjob", song : "icecube", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/GoodAssJob/thatsmybitch.mp3", index : {album : "goodassjob", song : "thatsmybitch", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/GoodAssJob/soappalled.mp3", index : {album : "goodassjob", song : "soappalled", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/GoodAssJob/makehersay.mp3", index : {album : "goodassjob", song : "makehersay", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/GoodAssJob/seemeagain.mp3", index : {album : "goodassjob", song : "seemeagain", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/GoodAssJob/higher.mp3", index : {album : "goodassjob", song : "higher", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/Yandhi/thestorm.mp3", index : {album : "yandhi", song : "thestorm", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/Yandhi/newbody.mp3", index : {album : "yandhi", song : "newbody", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/Yandhi/byebyebaby.mp3", index : {album : "yandhi", song : "byebyebaby", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/Yandhi/loveit.mp3", index : {album : "yandhi", song : "loveit", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/Yandhi/hurricane1.mp3", index : {album : "yandhi", song : "hurricane1", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/Yandhi/alien.mp3", index : {album : "yandhi", song : "alienspacex", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/Yandhi/lastname.mp3", index : {album : "yandhi", song : "lastname", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/Yandhi/cityinthesky.mp3", index : {album : "yandhi", song : "cityinthesky", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/Yandhi/wegotlove.mp3", index : {album : "yandhi", song : "wegotlove", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/Yandhi/chakras.mp3", index : {album : "yandhi", song : "chakras", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/ThankGodForDrugs/iamnothome.mp3", index : {album : "thankgodfordrugs", song : "iamnothome", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/ThankGodForDrugs/onsight.mp3", index : {album : "thankgodfordrugs", song : "onsight", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/ThankGodForDrugs/blkkkskinhead.mp3", index : {album : "thankgodfordrugs", song : "blkkkskinhead", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/ThankGodForDrugs/god.mp3", index : {album : "thankgodfordrugs", song : "god", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/ThankGodForDrugs/newslaves.mp3", index : {album : "thankgodfordrugs", song : "newslaves", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/ThankGodForDrugs/senditup.mp3", index : {album : "thankgodfordrugs", song : "senditup", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/ThankGodForDrugs/yeezus.mp3", index : {album : "thankgodfordrugs", song : "yeezus", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/ThankGodForDrugs/talktome.mp3", index : {album : "thankgodfordrugs", song : "talktome", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/ThankGodForDrugs/bloodontheleaves.mp3", index : {album : "thankgodfordrugs", song : "bloodontheleaves", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/ThankGodForDrugs/louderiguilttripped.mp3", index : {album : "thankgodfordrugs", song : "louderiguilttripepd", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/ThankGodForDrugs/emotions.mp3", index : {album : "thankgodfordrugs", song : "emotions", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/ThankGodForDrugs/perfectbitch.mp3", index : {album : "thankgodfordrugs", song : "perfectbitch", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/ThankGodForDrugs/awesome.mp3", index : {album : "thankgodfordrugs", song : "awesome", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/ThankGodForDrugs/oneilove.mp3", index : {album : "thankgodfordrugs", song : "oneilove", artist : "kanyewest"}},
    {src : baseURL+"Songs/KanyeWest/ThankGodForDrugs/bound.mp3", index : {album : "thankgodfordrugs", song : "bound", artist : "kanyewest"}},
];


var albumIndex = [
    {src:baseURL+"Songs/KanyeWest/GoodAssJob/livefastdieyoung.mp3", name:"goodassjob"},
    {src:baseURL+"Songs/KanyeWest/Yandhi/thestorm.mp3", name:"yandhi"},
    {src:baseURL+"Songs/KanyeWest/ThankGodForDrugs/iamnothome.mp3", name:"thankgodfordrugs"},
];

var songQueue = [];
var curQueueIndex;

var searchArtist = document.getElementById('search-artist');
var searchSong = document.getElementById('search-song');
var searchAlbum = document.getElementById('search-album');

function queryAlbum(){
    var album = replaceSearch(searchAlbum.value) || null;

    document.getElementById("result-header").innerHTML = "<p id='result-placeholder'>Searching..</p>";
    var results = albumIndex.filter(
        (filtered) => filtered.name.includes(album)
    )

    if(!album){
        results = albumIndex;
    }

    if (!results || results.length == 0){
        document.getElementById("result-header").innerHTML = "<p id='result-placeholder'>No Results</p>";
    }

    makeAlbumResults(results);
}

function querySongs(list){
    var song = replaceSearch(searchSong.value) || null;

    var results;
    if(song){
        results = list.filter(
            (filtered) => filtered.index.album.includes(song)
        );
    }else{
        results = list;
    }
    //console.log(results);
    document.getElementById("result-header").innerHTML = "<p id='result-placeholder'>Searching..</p>";
    if(results.length == 0){
        document.getElementById("result-header").innerHTML = "<p id='result-placeholder'>No Results</p>";
        return;
    }

    songQueue = [];
    curQueueIndex = 0;

    makeResults(results);

    for(let i = 0; i < results.length; i++){
        var curResult = results[i];
        songQueue[i] = curResult.src;
    }

    console.log(songQueue);
}

async function makeResults(results){
    var newResults = [];
    for(let i = 0; i < results.length; i++){
        try{
            let cur = results[i].src;
            let metadata = await loadSong(cur);
            let title = metadata[0].title;
            let album = metadata[0].album;
            let cover = metadata[1];

            console.log(cur);
            makeResult(cur, title, album, "", cover, function(){
                console.log(cur);
                setCurrent(cur);
                changeTrack(cur);
                if(!playing){
                    pausePlay();
                }
                curQueueIndex = songQueue.indexOf(cur);
            });
        }catch(err){
            console.log(err);
        }
    }
    document.getElementById("result-placeholder").innerHTML = "";
}

async function makeAlbumResults(results){
    var newResults = [];
    for(let i = 0; i < results.length; i++){
        try{
            let cur = results[i].src;
            let metadata = await loadSong(cur, true);
            let title = metadata[0].album;
            let cover = metadata[1];

            makeResult(cur, title, "", "", cover, function(){
                loadAlbum(results[i]);
            }, true);
        }catch(err){
            console.log(err);
        }
    }
    document.getElementById("result-placeholder").innerHTML = "";
}

function replaceSearch(input){
    var replacement = input.replace(/[.,\/#!$%\^&\*;:{}=\-_`~()]/g,"");
    console.log(replacement.toLowerCase());
    return replacement.toLowerCase();
}

function dumpAll(){
    var results;
    for(var i = 0; i < songIndex.length; i++){
        results[i] = songIndex[i].src;
    }
    makeResults(results);
}

async function makeResult(dir, title, album, artist, cover, click, makeCover){
    var header = document.getElementById('result-header');
    try{
        var resultClick = document.createElement('a');
        var newResult = document.createElement('div');
        var resultSong = document.createElement('div');
        var resultAlbum = document.createElement('div');
        var resultCover = document.createElement('img');

        resultClick.onclick = click;
        resultClick.className = "result-click";
        newResult.className = "search-result";
        
        resultSong.className = "result-song";
        resultAlbum.className = "result-album";
        resultCover.className = "result-img";
        resultSong.innerHTML = title;
        resultAlbum.innerHTML = album;
        resultCover.src = cover;

        newResult.appendChild(resultSong);
        newResult.appendChild(resultAlbum);
        if(makeCover){
            newResult.appendChild(resultCover);
        }
        resultClick.appendChild(newResult);

        header.appendChild(resultClick);
        
    } catch(err){
        console.log(err);
    }
}

function loadAlbum(album){
    var id = albumIndex.indexOf(album);
    window.location.href = baseURL+"album.html?id=" + String(id);
}

async function getAlbumLength(lengths){
    return new Promise((resolve, reject) => {
        var secs = 0;
        for(var i = 0; i < lengths; i++){
            secs+=lengths[i];
        }
        var minutes = Math.floor(secs/60);
        var hours = Math.floor(minutes/60);

        resolve(String(hours).padStart(2, '0') + ":" + String(minutes).padStart(2, '0'));
    });
}