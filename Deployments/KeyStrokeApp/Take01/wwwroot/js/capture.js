// Please see documentation at https://docs.microsoft.com/aspnet/core/client-side/bundling-and-minification
// for details on configuring this project to bundle and minify static web assets.

// Write your JavaScript code.

var uptimes = [];
var downtimes = [];


function reportTimes() {
    var reportString = "";
    for (var i = 0; i < times.length - 1; ++i) {
        reportString += (i + 1) + ": " + (uptimes[i + 1].timestamp - uptimes[i].timestamp) + " ";
    }
    return reportString; // add this somewhere or alert it
}

$(document).ready(function () {


    $('#typearea').keyup(function (evt) {

        if (evt.which != 16)  // ignore shift key
        {
            if (evt.which == 13) // detected carriage return key press
            {
                evt.preventDefault();

            }
            uptimes.push({
                "timestamp": evt.timeStamp,
                "keycode": evt.which
            });

            if (evt.which == 13) // Send lick event
            {
                $('#showResults').click();

            }

        }
        //alert('Time captured:' + times[times.length-1].timestamp);
    });

    $('#typearea').keydown(function (evt) {
        if (evt.which != 16) // ignore shift key
        {
            if (evt.which == 13) // detected carriage return key press
            {
                evt.preventDefault();
            }

            //if (evt.which == 13) alert('ENTER pressed!');
            downtimes.push({
                "timestamp": evt.timeStamp,
                "keycode": evt.which
            });
        }
        
        //alert('Time captured:' + times[times.length-1].timestamp);
    });

    $('#showResults').click(function (evt) {

        // Get Verification Token value
        var token = $('input[name="__RequestVerificationToken"]').val();

        $.ajax({
            type: "POST",
            url: "Index",
            headers: {
                RequestVerificationToken: token
            },
            data: {
                "uptimes": uptimes,
                "downtimes": downtimes
            },
            success: function (data) {
                $('#totalKeystroke').html("<b>Captured " + downtimes.length.toString() + " key presses</b>");
                //evt.preventDefault();
            },
            error: function (response, status, err) {
                alert("Failure: " + response.responseText);
            }
        });


        //var display = reportTimes();
        //console.log(display);
        //alert('Uptime is ' + uptimes[1].timestamp);
        //return false;
    });

    // call this to get the string

});

