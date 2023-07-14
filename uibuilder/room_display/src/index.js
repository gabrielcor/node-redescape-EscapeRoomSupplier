// To prevent the video constantly restarting, we only update the src element
// if it has changed
var lastVideoOverlaySrc = "";
var lastVideoBackgroundSrc = "";
 
var app = new Vue({
    // The HTML element to attach to
    el: '#app',
    // Variables defined here will be avalable and updated within the HTML
    data: {
        msg: '[No Message Received Yet]',
    },
    // Callback function when Vue library is fully loaded
    mounted: function() {
        // Start up uibuilder
        uibuilder.start();
        // Keep a reference to the Vue app
        var vueApp = this;
        // Callback triggered when node receives a (non-control) msg
        uibuilder.onChange('msg', function(msg) {
            vueApp.msg = msg;
            if (msg.videoOverlaySrc != lastVideoOverlaySrc) {
                vueApp.$refs.videoOverlay.src = msg.videoOverlaySrc;
                lastVideoOverlaySrc = msg.videoOverlaySrc;
            }
            if (msg.videoBackgroundSrc != lastVideoBackgroundSrc) {
                vueApp.$refs.videoBackground.src = msg.videoBackgroundSrc;
                lastVideoBackgroundSrc = msg.videoBackgroundSrc;
            }
        });
            
    },
});