function initAlbum(){
    var id = new URLSearchParams(window.location.search).get("id");

    if(!id){
        return;
    }

    var src = albumIndex[id];

    loadAlbumData(src.src);

    var results;

    results = songIndex.filter(
        (filtered) => filtered.index.album.includes(src.name)
    )
    
    curQueueIndex = 0;

    for(let i = 0; i < results.length; i++){
        var curResult = results[i];
        songQueue[i] = curResult.src;
    }

    console.log(songQueue);

    makeAlbumSongResults(results);
}

async function loadAlbumData(src){
    try{
        var metadata = await loadSong(src, true);
        var title = metadata[0].album;
        var cover = metadata[1];

        var albumCover = document.getElementById('main-album-cover');
        albumCover.src = cover;
        var albumTitle = document.getElementById('main-album-title');
        albumTitle.innerHTML = title;

        //setCurrent(src, title);
    }catch(err){
        console.log(err);
    }
}

async function makeAlbumSongResults(results){
    for(let i = 0; i < results.length; i++){
        try{
            let cur = results[i].src;
            let metadata = await loadSong(cur);
            let title = metadata[0].title;
            let album = metadata[0].album;
            let cover = metadata[1];

            makeSongResult(cur, title, album, "", cover, function(){
                setCurrent(cur);
                changeTrack(cur);
                if(!playing){
                    pausePlay();
                }
                curQueueIndex = songQueue.indexOf(cur);
                console.log(curQueueIndex);
            });
            if(i == 0){
                console.log(cur);
                setCurrent(cur);
                changeTrack(cur);
                curQueueIndex = songQueue.indexOf(cur);
            }
        }catch(err){
            console.log(err);
        }
    }
}

async function makeSongResult(dir, title, album, artist, cover, click, makeCover){
    var header = document.getElementById('album-song-header');
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