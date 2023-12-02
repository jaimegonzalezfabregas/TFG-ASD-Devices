var express = require('express');
// var https = require('https');
var http = require('http');
var fs = require('fs');
var bodyparser = require('body-parser');

const PORT = Number.parseInt(process.argv[0]) || 8888;

// This line is from the Node.js HTTPS documentation.
var options = {
    key: fs.readFileSync('../keys/https/server_key.pem'),
    cert: fs.readFileSync('../keys/https/server_cert.pem')
};

var app = express();
app.use(bodyparser.json({ limit: '50mb' }));


app.post("/rpc", (req, res) => {
    let { devicename } = req.headers
    let { method, params } = req.body
    console.log("url: ", req.originalUrl, params, method, devicename);

    if (method == "ping") {
        res.json({ "method": "pong", "response": { "epoch": Math.floor(Date.now() / 1000), "ok": true } })
    } else if (method == "qr") {

        res.json({ "method": "qr_res", "response": { "text": "qr recibido, contenido era: " + params.qr_content, "duration": 17, "icon_id": Math.floor(Math.random() * 2.999), "ok": true } })
    }
    else {
        res.json({ "ok": true })
    }
})

app.use('/ota', express.static(__dirname + '/ota'));

/* rpc to display text on the device
{
    "method": "display_text",
    "params": {
        "text": "Hello World"
        "duration": 5
    }
}
callType is either oneway or twoway;
send that in a post to http://thingsboard.asd:8080/api/plugins/rpc/{callType}/{deviceId}
*/




http.createServer(app).listen(8888);
// https.createServer(options, app).listen(PORT);


console.log("https server started on port", PORT)