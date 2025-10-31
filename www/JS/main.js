var jsmediatags = window.jsmediatags;

var albumCoverData;

var playingImageDisplay = document.getElementById('playing-image');
var playingTitleDisplay = document.getElementById('playing-title');
var playingArtistDisplay = document.getElementById('playing-artist');
var playingAlbumDisplay = document.getElementById('playing-album');

function loadSong(dir, loadalbum){
    return new Promise((resolve, reject) =>{
        jsmediatags.read(dir,{
            onSuccess: function(tag) {
                const image = tag.tags.picture;

                if (image && loadalbum) {
                    // Convert binary data to base64 string
                    let base64String = "";
                    for (let i = 0; i < image.data.length; i++) {
                        base64String += String.fromCharCode(image.data[i]);
                    }
                
                    // Encode to base64
                    const base64 = btoa(base64String);

                    // Create data URI
                    const dataUri = `data:${image.format};base64,${base64}`;

                    albumCoverData = dataUri;


                }else{
                    if(loadalbum){
                        console.error("Couldn't load album cover image");
                    }
                }
                resolve([tag.tags,albumCoverData]);
            },
            onError: function(error) {
                console.log(':(', error.type, error.info);
                reject(error);
            }
        })
    })
}

async function setCurrent(dir, altTitle, loadAlbum){
    try{
        var loadedSong = await loadSong(dir, true);
        playingTitleDisplay.innerHTML = loadedSong[0].title;
        if(altTitle){
            playingTitleDisplay.innerHTML = altTitle;
        }
        playingArtistDisplay.innerHTML = loadedSong[0].artist;
        if(loadAlbum){
            playingAlbumDisplay.innerHTML = loadedSong[0].album;
        }
        playingImageDisplay.src = loadedSong[1];
    } catch(err){
        console.error(err);
    }
}