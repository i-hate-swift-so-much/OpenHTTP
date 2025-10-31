var playerHeader = document.getElementById("player-header");
var player = document.getElementById("audio-player");
var pausePlayButtom = document.getElementById("pause-play-img");

var playing = false;

var srcSet = false;

var curSrc = "";

function pausePlay(){
    if(!srcSet){
        return;
    }

    playing = !playing;
    

    var method = playing ? 'play' : 'pause';

    player[method]();

    //console.log(formatUnixTime(player.duration));
    //console.log(player.duration);
}

function changeTrack(src){
    player.src = src;
    cuSrc = src;
    srcSet = true;

    var method = playing ? 'play' : 'pause';

    player[method]();
    //player.load  
}

var timeDisplay = document.getElementById('player-time-display');

player.ontimeupdate = (event) => {
    timeDisplay.innerHTML = formatUnixTime(player.currentTime) + " - " + formatUnixTime(player.duration);
};

player.onload = (event) => {
    timeDisplay.innerHTML = formatUnixTime(player.currentTime) + " - " + formatUnixTime(player.duration);
}

player.onended = (event) => {
    nextSong();
}

player.onpause = (event) => {
    pausePlayButtom.src = baseURL+"Images/Buttons/Play.png";
}

player.onplay = (event) =>{
    pausePlayButtom.src = baseURL+"Images/Buttons/Pause.png";
}

function lastSong(){
    if(songQueue.length == 1){
        changeTrack(curSrc);
    }else if (curQueueIndex == 0){
        curQueueIndex = songQueue.length - 1;
        changeTrack(songQueue[curQueueIndex]);
        setCurrent(songQueue[curQueueIndex]);
    }else{
        curQueueIndex -= 1;
        changeTrack(songQueue[curQueueIndex]);
        setCurrent(songQueue[curQueueIndex]);
    }
    if(!playing){
        pausePlay();
    }
    console.log(curQueueIndex);
}

function nextSong(){
    if(songQueue.length == 1){
        changeTrack(curSrc);
    }else if(songQueue.length-1 == curQueueIndex){
        curQueueIndex = 0;
        changeTrack(songQueue[curQueueIndex]);
        setCurrent(songQueue[curQueueIndex]);
    }else{
        curQueueIndex += 1;
        changeTrack(songQueue[curQueueIndex]);
        setCurrent(songQueue[curQueueIndex]);
    }
    if(!playing){
        pausePlay();
    }
    console.log(curQueueIndex);
}

function formatUnixTime(seconds){
    var minutes = seconds / 60 ||'0';

    var newSecs = seconds % 60 || '0';

    return String(Math.floor(minutes)).padStart(2, '0') + ":" + String(Math.floor(newSecs)).padStart(2, '0');
}