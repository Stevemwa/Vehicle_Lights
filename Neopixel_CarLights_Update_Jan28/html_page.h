const char html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang=en>

<head>
    <meta charset=UTF-8>
    <title>Ricahrd's Car Control</title>
    <meta name=viewport content="width=device-width, initial-scale=1">
    <meta name=theme-color content="#333" />
    <link href="https://fonts.googleapis.com/css2?family=Permanent+Marker&display=swap" rel=stylesheet>
    <style>
        body {
            min-height: 100vh;
            margin: 0;
            padding: 0;
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
            font-family: "Permanent Marker", cursive;
            color: #ccc;
            color-scheme: dark;
            text-shadow: 0 2px 9px rgba(85, 34, 0, 0.911);
            user-select: none;
            background: linear-gradient(230deg, #100101, #9b59a6, #3498db)
        }

        #app {
            width: 100%;
            max-width: 1400px;
            min-height:1000px;
            background-color: rgba(0, 0, 0, 0.1);
            box-shadow: 0 0 80px rgba(0, 0, 0, 9);
            padding: px;
            border-radius: 5px;
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 15px
        }

        #apptitle {
            width: 100%;
            margin-top: 10px;
            display: flex;
            flex-direction: column;
            align-items: center;
            gap: 5px;
            opacity: 0;
            animation: slideDown .5s forwards
        }

        .container {
            display: flex;
            justify-content: space-between;
            margin: 50px
        }

        .input-group {
            display: flex;
            align-items: center;
            margin: 10
        }

        label {
            font-size: 15px
            padding:1px;
            align-items: center;
            color: #eee;
            border-radius: 20px;
            text-align: center;
            width: auto;
            margin-right: 5px
        }

        select,
        input[type="number"],
        input[type="range"],
        input[type="color"] {
            width: 70%;
            padding: 5px;
            margin-top: 10px;
            border-radius: 5px;
            background-color: rgba(240, 240, 240, 0.61);
            outline: 0
        }

        button {
            font-size: 15px;
            background-color: #007bff;
            border: 0;
            font-family: "Permanent Marker", cursive;
            border-radius: 5px;
            padding: 10px;
            color: #fff;
            cursor: pointer
        }

        #rangeBlock,
        #colorSelect,
        #SaveButton,
            {
            display: auto;
            flex-direction: column;
            align-items: center;
            gap: 10px;
            padding: 10px;
            background-color: rgba(0, 0, 0, 0.4);
            border-radius: 5px;
            background: radial-gradient(rgba(255, 255, 255, 0.6), #000000);
            margin-top: 30px;
            width: 100%
        }

        #effectsList {
            display: none;
            flex-direction: column;
            align-items: center;
            padding: 5px;
            font-size: 20px;
            min-height: 40vh;
            overflow-y: auto;
            gap: 3px
        }

        #effectsList span {
            background: linear-gradient(30deg, #9b59b6, #3498db);
            color: #fff;
            border-radius: 20px;
            padding: 15px;
            font-size: 15px;
            display: flex;
            flex-direction: column;
            align-items: center;
            margin-bottom: 10px;
            animation: slideDownAndFade 1s
        }

        @media only screen and (max-width:768px) {
            #apptitle {
                margin-top: 5%;
                font-size: 24px
            }
            #rangeBlock,
            #colorSelect {
                padding: 10px
            }
            #effectsList {
                font-size: 18px
            }
            #effectsList span {
                font-size: 15px
            }
            .input-container {
                flex-direction: column
            }
            .input-container label {
                text-align: right;
                padding-right: 1
            }
        }

        #panel {
            display: flex;
            justify-content: space-between;
            align-items: center;
            font-weight: bold;
            position: fixed;
            height: 45px;
            width: 100vw;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: rgba(0, 0, 0, 6.5);
            color: #fff;
            font-size: 20px;
            padding: 0 20px
        }

        #panel>:first-child,
        #panel>:last-child {
            flex-grow: 2;
            text-align: center
        }

        input[type="checkbox"] {
            margin-right: 5px
        }

/* Container to hold all the buttons */
#buttonContainer {
    display: flex;
    flex-direction: column;   /* Stack buttons vertically */
    align-items: flex-start;  /* Align buttons to the left */
    justify-content: flex-start;  /* Start from the top */
    position: absolute;          /* Fix the container to the left of the screen */
    left: 0;                  /* Align to the left of the viewport */
    top: 60px;                /* Optional: distance from the top */
    padding: 10px;            /* Optional: padding around the container */
}

/* Style for each button */
#SaveSetting, #editCarName, #uploadImageButton, #saveImageButton, #saveCarName {
    font-size: 15px;
    background-color: #5dade2;
    border: 0;
    border-radius: 5px;
    padding: 1px;
    color: #fff;
    cursor: pointer;
    margin-bottom: 10px; /* Optional: space between buttons */
}

/* Hover effect for buttons */
#SaveSetting:hover,
#editCarName:hover,
#uploadImageButton:hover,
#saveImageButton:hover,
#saveCarName:hover {
    background-color: #1200b3;
}
        h1#carTitle {
            text-align: center;
            font-size:40px;
            margin-top: 200px;
            background-color: rgba(0, 0, 0, 0.4);
            color: #fff;
            border-radius: 10px;
            box-shadow: 0 4px 10px rgba(0, 0, 0, 0.9);
            position:flex;
        }

        @media only screen and (max-width:600px) {
            #editCarName,
                {
                width: 100%;
                position: static;
                margin-bottom: 10px
            }
        }

        #basicControls {
            animation: slideInRightAndFade 1s forwards
        }

        #colorSelect,
        #toggleStripButton,
        #toggleBasicControls,
        #Effectbutton {
            animation: cascadeDownAndFade .5s ease-out
        }

        #colorSelect {
            animation-delay: .6s
        }

        #toggleStripButton {
            animation-delay: .2s
        }

        #toggleBasicControls {
            animation-delay: .4s
        }

        #Effectbutton {
            animation-delay: 1s
        }

        #strobebox,
        #leftFreq,
        #leftScem,
        #RightFreq,
        #RightScem,
        #BlinkerAnimation,
        #colorSettings,
        #basicControls,
        #stripSettingsContainer
        {
            padding: 8px;
            font-size: 15px;
            border: 1px solid #ccc;
            border-radius: 5px;
            background-color: #555;
            color: #fff;
            outline: 0;
            cursor: pointer;
            margin: 5px
        }
#StartAnimation,#LeftDirection,#RightDirection{
            padding: 8px;
            font-size: 15px;
            border: 1px solid #ccc;
            border-radius: 5px;
            background-color: #555;
            color: #fff;
            outline: 0;
            cursor: pointer;
            margin: 5px
}
        #stripSettingsContainer {
            opacity: 0;
            animation: fadeIn 1s forwards;
            display: none;
            text-align: center
        }

        .input-group {
            display: inline-block;
            text-align: left;
            margin-top: 20px
        }

        #BlinkerTypeLabel {
            font-weight: bold;
            display: block;
            margin-bottom: 5px
        }

        #BlinkerHeader {
            font-size: 24px;
            font-weight: bold;
            margin-bottom: 10px
        }

        input[type="text"] {
            display: none;
            width: 50%;
            padding: 10px;
            font-size: 14px;
            border: 1px solid #ccc;
            border-radius: 5px;
            box-sizing: border-box;
            margin: 10px auto;
            text-align: left
        }

        #CurrentAnimation {
            border: 2px solid #;
            border-radius: 5px;
            padding: 5px;
            background-color: #555
        }

        @keyframes slideDown {
            from {
                transform: translateY(-20px);
                opacity: 0
            }
            to {
                transform: translateY(0);
                opacity: 1
            }
        }

        @keyframes fadeIn {
            from {
                opacity: 0
            }
            to {
                opacity: 1
            }
        }

        @keyframes slideInRightAndFade {
            from {
                transform: translateX(100%) translateY(0);
                opacity: 0
            }
            to {
                transform: translateX(0) translateY(0);
                opacity: 1
            }
        }

        @keyframes slideDownAndFade {
            from {
                transform: translateY(-100%) translateX(0);
                opacity: 0
            }
            to {
                transform: translateY(0) translateX(0);
                opacity: 1
            }
        }

        @keyframes cascadeDownAndFade {
            from {
                transform: translateY(-100%) translateX(0);
                opacity: 0
            }
            to {
                transform: translateY(0) translateX(0);
                opacity: 1
            }
        }
    </style>
</head>

<body>
    <div id="app">
        <div id="apptitle" style="position:relative">
            <h1 id="carTitle">Richard's Car</h1>
            <input type="text" id="carNameInput" style="display:none">
        </div>
        <div id="buttonContainer">
            <button id="uploadImageButton">Upload Image</button>
            <button id="saveImageButton" style="display:none">Save Image</button>
            <button id="saveCarName" style="display:none">Save Name</button>
            <button id="editCarName">Edit Name</button>
<button id="SaveSetting" style="padding:1px;">Save Settings</button>
<p id="SaveMessage" style="color: white; display: none;">Settings have been saved!</p> 
        </div>
        <div id="backgroundSection">
            <input type="file" id="imageInput" accept=".png,.jpg,.jpeg,.gif,.bmp,.webp" style="display: none;">
        </div>

        <button id="toggleStripButton" onclick="toggleStripSettings()">Strip Settings</button>

<div class="container" id="stripSettingsContainer" style="display:none">
    <div class="strip-box" style="text-align:center; align-items:center;">
        <h1 style="font-size:20px;">Animation Types</h1>
    </div>
    <div class="input-group">
        <label for="BlinkerAnimation">Blinker Animation:</label>
        <select id="BlinkerAnimation" name="Blinkertype" onchange="BlinkerAnimation()">
            <option value="1">Heartbeat</option>
            <option value="2">Sequential</option>
            <option value="3">Blinker</option>
            <option value="4">Sequential Solid</option>
        </select>
    </div>

    <div class="input-group">
<label for="StartAnimation" style="font-size:15px;">Car Start Animation:</label>
        <select id="StartAnimation" name="CarStartType" onchange="StartAnimation()">
            <option value="1">Blink</option>
            <option value="2">Sequential</option>
            <option value="3">Stack</option>
            <option value="4">Fade In</option>
        </select>
    </div>
            <div class=strip-box style=text-align:center;align-items:center>
                <h1 style=font-size:20px>Left Strip</h1>
                <div style=text-align:center>
                    <label for=nleft>No. of LEDs:</label><br>
                    <input type=number id=nleft name=nleft min=1 max=150 value=60 onchange=nleft()>
                </div>
            </div>
    <div class="input-group">
        <label for="LeftDirection">Left Blinker Direction:</label>
        <select id="LeftDirection" name="Blinkertype" onchange="LeftDirection()">
            <option value="1">Left</option>
            <option value="2">Right</option>
        </select>
    </div>
            <div class=input-group>
                <label for=leftFreq>Frequency:</label>
                <select id=leftFreq name=leftFreq onchange=leftFreq()>
<option value=1>800KHz Stream</option>
<option value=0>400KHz Stream</option>
</select>
            </div>
            <div class=input-group>
                <label for=leftScem>Color Scheme:</label>
                <select id=leftScem name=leftScem onchange=leftScem()>
<option value=1>GRBW</option>
<option value=2>RGBW</option>
<option value=3>BRGW</option>
<option value=4>RGB</option>
<option value=5>GRB</option>
<option value=6>BRG</option>
</select>
            </div>
            <div id=Rstrip class=strip-box>
                <h1 style=text-align:center;font-size:20px>Right Strip</h1>
                <div class=input-container style=text-align:center;display:flex;flex-direction:column;align-items:center>
                    <label for=nRight>No. of LEDs:</label>
                    <input type=number id=nRight name=nRight min=1 max=150 value=60 onchange=nRight()>
                </div>
    <div class="input-group">
        <label for="RightDirection">Right Blinker Direction:</label>
        <select id="RightDirection" name="Blinkertype" onchange="RightDirection()">
            <option value="1">Left</option>
            <option value="2">Right</option>
        </select>
    </div>
                <div class=input-group>
                    <label for=RightFreq>Frequency:</label>
                    <select id=RightFreq name=RightFreq onchange=RightFreq()>
<option value=1>800KHz Stream</option>
<option value=0>400KHz Stream</option>
</select>
                </div>
                <div class=input-group>
                    <label for=RightScem>Color Scheme:</label>
                    <select id=RightScem name=RightScem onchange=RightScem()>
<option value=1>GRBW</option>
<option value=2>RGBW</option>
<option value=3>BRGW</option>
<option value=4>RGB</option>
<option value=5>GRB</option>
<option value=6>BRG</option>
</select>

                </div>
                <div id=StripSelection>
                    <select id=StripSelect name=StripSelect onchange=StripSelect() style=display:none;align-items:center>
<option value=3 selected>All</option>
</select>
                    <h1 style=text-align:center;font-size:20px>Strobe Effect on DRL</h1>
                    <h1>Strobe Effect on DRL</h1>
                    <select id=strobebox onchange=Strobe()>
<option value=1>Yes</option>
<option value=2>No</option>
</select>
                </div>
            </div>
        </div>
<div id="rangeBlock">
    <div style="text-align:center">
        <button id="toggleBasicControls" onclick="toggleControls()">Basic Controls</button>
    </div>
    <div id="basicControls" style="opacity:0; display:none">
        <h1 style="text-align:center; font-size:20px;">Basic Control</h1>

        <!-- Brightness Control -->
        <div style="text-align: center; margin-bottom: 10px;">
            <span style="display: block; text-align: center;">Brightness</span>
            <input id="rangeBrightness" oninput="outputBrightness.value=this.value" type="range" value="25" min="0" max="100" />
            <output id="outputBrightness">25</output>
        </div>

        <!-- Effect Time Control (Hidden) -->
        <div style="text-align: center; margin-bottom: 10px; display: none;">
            <span style="display: block; text-align: center;">Effect Time</span>
            <input id="rangeDuration" oninput="outputDuration.value=this.value" type="range" value="5" min="0" max="10" />
            <output id="outputDuration">5</output>
        </div>

        <!-- Blinker LEDs Control -->
        <div style="text-align: center; margin-bottom: 10px;">
            <span style="display: block; text-align: center;">Blinker LEDs</span>
            <input id="BlinkerLeds" oninput="bLEDs.value=this.value" type="range" value="60" min="1" max="150" />
            <output id="bLEDs">60</output>
        </div>

        <!-- Blinker/Animation Speed Control -->
        <div style="text-align: center; margin-bottom: 10px;">
            <span style="display: block; text-align: center;">Blinker Speed</span>
            <input id="BlinkerSpeed" oninput="bSpeed.value=this.value" type="range" value="5" min="0" max="100" />
            <output id="bSpeed">5</output>
        </div>
        <!-- Switchback Mode -->
        <div id="switchbackbox" style="text-align:center; animation:fadeIn 1s forwards">
            <h1 style="text-align:center; font-size:20px;">Switchback Mode</h1>
            <select onchange="toggleSwitchback()" style="border:2px solid #007bff; padding:5px; background-color:rgba(255,255,255,0.4)">
                <option value="1">ON</option>
                <option value="2" selected>OFF</option>
            </select>
        </div>
    </div>
</div>

        <div id=colorSelect>
            <button id=toggleColorSettings onclick=toggleColorSettings()>Strip Color Settings</button>
            <div id=colorSettings style="display:none;animation:cascadeDownAndFade .5s ease-out">
                <h1 style=text-align:center;font-size:20px>Color Control</h1>
                <div>
                    <span>Left Strip</span>
                    <input type=color id=Lcolor value=#00FF00 onchange=Lcolor() />
                </div>
                <div>
                    <span>Right Strip</span>
                    <input type=color id=Rcolor value=#00ff00 onchange=Rcolor()>
                </div>
                <div>
                    <span>Extra Strip</span>
                    <input type=color id=Ecolor value=#ff0000 onchange=Ecolor()>
                </div>
                <div>
                    <span>DRL Color</span>
                    <input type=color id=DRLcolor value=#FFFFFF onchange=DRLcolor()>
                </div>
                <div>
                    <span>Brake Color</span>
                    <input type=color id=BrakColor value=#FF0000 onchange=BrakColor()>
                </div>
            </div>
        </div>
<button id="Effectbutton" onclick="toggleEffectsList()">Effects List</button>

<div id="currentEffectElem" class="animated-element" style="display: block,font-size:25px;color:white;background:linear-gradient(45deg,#ff0000 0,#800080 50%,#000000 100%);border-radius:10px 20px 30px 40px">
  <div>

  </div>
</div>

<!-- Separate container for the slider -->
<div id="effectSpeedContainer" style="display:none;">
        <span style="display: block; text-align: center;">Animation Speed</span>
  <input id="EffectSpeed" oninput="effectSpeedValue.value=this.value" type="range" value="5" min="0" max="255" />
  <output id="effectSpeedValue">5</output>
</div>
        <div id=effectsList>
<span data-effect=1>WhiteoverRainbow</span>
<span data-effect=2>Rainbow Loop 1</span>
<span data-effect=3>Rainbow Loop 2</span>
<span data-effect=4>Color Wipe</span>
<span data-effect=5>Random March</span>
<span data-effect=6>RGB Propeller</span>
<span data-effect=7>Fire</span>
<span data-effect=8>Blue Fire</span>
<span data-effect=9>Random Burst</span>
<span data-effect=10>Flicker</span>
<span data-effect=11>Random Color Pop</span>
<span data-effect=12>Sparkle</span>
<span data-effect=13>Rotating Red Blue</span>
<span data-effect=14>Snow Sparkle</span>
<span data-effect=15>RWB March</span>
<span data-effect=16>Theater Chase Rainbow</span>
<span data-effect=17>Strobe</span>
<span data-effect=18>Police Blinker</span>
<span data-effect=19>KITT</span>
<span data-effect=20>Swipe Random Animation</span>
<span data-effect=21>Solid Animation</span>
<span data-effect=22>Blend</span>
<span data-effect=23>Blend 2</span>
<span data-effect=24>Center to Outside</span>
<span data-effect=25>Outside to Center</span>
<span data-effect=26>Left to Right</span>
<span data-effect=27>Candy Cane</span>
<span data-effect=28>Dissolve Random</span>
<span data-effect=29>Rainbow Runner</span>
<span data-effect=30>Knight Rider</span>
<span data-effect=31>MiddleOut(Repeat)</span>
<span data-effect=32>MiddleOutReset</span>
<span data-effect=33>Breathe Animation</span>
<span data-effect=34>Color Bounce</span>
<span data-effect=35>Color Bounce Rain</span>
<span data-effect=36>Scanner</span>
<span data-effect=37>stackingAnimation</span>
<span data-effect=38>breatheAnimationRandom</span>
<span data-effect=39>StackRandomColor</span>


            <br><br><br><br>
        </div>
    </div>
    <div id=panel>
        <div>
            <input id=toggleLoop type="checkbox" />
            <label for=toggleLoop>LOOP</label>
        </div>
        <div style=display:flex;align-items:center;gap:10px>
            <button id=prevButton><</button>
            <div>
                <input id=togglePlay type="checkbox" />
                <label for=togglePlay>PLAY</label>
            </div>
            <button id=nextButton>></button>
        </div>
        <div>
            <input id=toggleRandom type="checkbox" />
            <label for=toggleRandom>RAND</label>
        </div>
    </div>
    </div>
    <SCRIPT>
        function isPanelOpen(panelId) {
            return document.getElementById(panelId).style.display === 'block';
        }

        function closeAllPanels() {
            document.getElementById('effectsList').style.display = 'none';
            document.getElementById('stripSettingsContainer').style.display = 'none';
            document.getElementById('colorSettings').style.display = 'none';
            document.getElementById('basicControls').style.display = 'none';
        }

        function toggleControls() {
            if (!isPanelOpen('basicControls')) {
                closeAllPanels();
            }
            document.getElementById('basicControls').style.display = isPanelOpen('basicControls') ? 'none' : 'block';
        }

function toggleEffectsList() {
    // Toggle the visibility of the 'effectsList' panel
    const effectsList = document.getElementById('effectsList');
    const effectSpeedContainer = document.getElementById('effectSpeedContainer');
    
    if (!isPanelOpen('effectsList')) {
        closeAllPanels();
    }

    // Toggle visibility of the effects list
    effectsList.style.display = isPanelOpen('effectsList') ? 'none' : 'block';

    // Toggle visibility of the effect speed slider
    if (effectsList.style.display === 'block') {
        effectSpeedContainer.style.display = 'block';  // Show the slider if the list is visible
    } else {
        effectSpeedContainer.style.display = 'none';   // Hide the slider if the list is hidden
    }
}

        function toggleStripSettings() {
            if (!isPanelOpen('stripSettingsContainer')) {
                closeAllPanels();
            }
            document.getElementById('stripSettingsContainer').style.display = isPanelOpen('stripSettingsContainer') ? 'none' : 'block';
        }

        function toggleColorSettings() {
            if (!isPanelOpen('colorSettings')) {
                closeAllPanels();
            }
            document.getElementById('colorSettings').style.display = isPanelOpen('colorSettings') ? 'none' : 'block';
        }

        function toggleEditSaveMode() {
            const carTitle = document.getElementById('carTitle');
            const carNameInput = document.getElementById('carNameInput');
            const editButton = document.getElementById('editCarName');
            const saveButton = document.getElementById('saveCarName');
            if (carTitle.style.display === 'none') {
                carTitle.innerText = carNameInput.value;
                carTitle.style.display = 'block';
                carNameInput.style.display = 'none';
                editButton.style.display = 'inline-block';
                saveButton.style.display = 'none';
                localStorage.setItem('carName', carNameInput.value);
            } else {
                carNameInput.value = carTitle.innerText;
                carTitle.style.display = 'none';
                carNameInput.style.display = 'inline-block';
                editButton.style.display = 'none';
                saveButton.style.display = 'inline-block';
            }
        }
        document.addEventListener('DOMContentLoaded', function() {
            const carTitle = document.getElementById('carTitle');
            const storedCarName = localStorage.getItem('carName');
            if (storedCarName) {
                carTitle.innerText = storedCarName;
            }
        });
        document.getElementById('editCarName').addEventListener('click', toggleEditSaveMode);
        document.getElementById('saveCarName').addEventListener('click', toggleEditSaveMode);

        function toggleUploadSaveMode() {
            const imageInput = document.getElementById('imageInput');
            const uploadButton = document.getElementById('uploadImageButton');
            const saveButton = document.getElementById('saveImageButton');
            const body = document.body;
            if (imageInput.style.display === 'none') {
                imageInput.style.display = 'block';
                uploadButton.style.display = 'none';
                saveButton.style.display = 'inline-block';
                imageInput.addEventListener('change', handleImageUpload);
            } else {
                imageInput.value = '';
                imageInput.style.display = 'none';
                uploadButton.style.display = 'inline-block';
                saveButton.style.display = 'none';
                imageInput.removeEventListener('change', handleImageUpload);
                const storedBackgroundImage = localStorage.getItem('backgroundImage');
                if (storedBackgroundImage) {
                    body.style.backgroundImage = `url('${storedBackgroundImage}')`;
                    body.style.backgroundSize = 'cover';
                    body.style.backgroundRepeat = 'repeat';
                    body.style.backgroundPosition = 'center center';
                } else {
                    body.style.backgroundImage = 'none';
                    body.style.backgroundSize = 'cover%';
                    body.style.backgroundRepeat = 'repeat';
                    body.style.backgroundPosition = 'center center';
                }
            }
        }

        function handleImageUpload() {
            const imageInput = document.getElementById('imageInput');
            const file = imageInput.files[0];
            if (file) {
                const reader = new FileReader();
                reader.onload = function(e) {
                    const img = new Image();
                    img.src = e.target.result;
                    img.onload = function() {
                        const isTall = img.height > window.innerHeight;
                        document.body.style.backgroundImage = `url('${e.target.result}')`;
                        document.body.style.backgroundRepeat = 'no-repeat';
                        document.body.style.backgroundPosition = 'center center';
                        document.body.style.backgroundSize = isTall ? 'auto 100%' : 'contain';
                        document.body.style.backgroundAttachment = 'fixed';
                        localStorage.setItem('backgroundImage', e.target.result);
                    };
                };
                reader.readAsDataURL(file);
            }
        }
        document.addEventListener('DOMContentLoaded', function() {
            const storedBackgroundImage = localStorage.getItem('backgroundImage');
            const body = document.body;
            if (storedBackgroundImage) {
                body.style.backgroundImage = `url('${storedBackgroundImage}')`;
                body.style.backgroundSize = '100%';
                body.style.backgroundRepeat = 'repeat';
                body.style.backgroundPosition = 'center center';
            } else {
                body.style.backgroundImage = 'none';
                body.style.backgroundSize = '100%';
                body.style.backgroundRepeat = 'repeat';
                body.style.backgroundPosition = 'center center';
            }
        });
        document.getElementById('uploadImageButton').addEventListener('click', toggleUploadSaveMode);
        document.getElementById('saveImageButton').addEventListener('click', toggleUploadSaveMode);
        window.onload = () => initWebSocket();
        const themeColor = 'FF1970';
        (function(color) {
            document.body.style.background = color;
            panel.style.background = color;
            const metaThemeColor = document.querySelector('meta[name=theme-color]');
            metaThemeColor.setAttribute('content', color);
        }(themeColor));
        effectsList.style.height = document.documentElement.clientHeight - (panel.clientHeight + rangeBlock.clientHeight + currentEffectElem.clientHeight + 20) + 'px';
        const COUNT = effectsList.children.length;
        let currentEffect = 1;
        let webSocket;

        function initWebSocket() {
            console.log('Trying to open a WebSocket connection...');
            webSocket = new WebSocket('ws://' + window.location.hostname + ':81/');
            webSocket.onopen = onOpen;
            webSocket.onclose = onClose;
            webSocket.onerror = onError;
            webSocket.onmessage = onMessage;
        }

        function onMessage(payload) {
            messageHandler(payload.data);
            console.log('Received: ', payload.data);
        }

        function onClose(e) {
            console.log('Connection closed ', e);
            setTimeout(initWebSocket, 1000);
        }

        function onError(e) {
            console.log(`[error]${e}`)
        }

        function onOpen() {
            console.log('Connection is success')
        }

        function messageHandler(payload) {
            let getData = (+payload.replace(/\D/g, ""));
            switch (payload[0]) {
                case 'E':
                    togglePlay.checked = true;
                    currentEffect = getData;
                    updateList(themeColor);
                    break;
                case 'B':
                    rangeBrightness.value = getData;
                    outputBrigthness.value = getData;
                    break;
                case 'D':
                    rangeDuration.value = getData;
                    outputDuration.value = getData + "s";
                    break;
                case 'J':
                    BlinkerLeds.value = getData;
                    bLEDs.value = getData;
                    break;
                case 'K':
                    BlinkerSpeed.value = getData;
                    bSpeed.value = getData + "s";
                    break;
                case 'v': 
                    EffectSpeed.value = getData; 
                    eSpeed.value = getData + " units"; 
                    break;
                case 'P':
                    if (getData === 1) {
                        togglePlay.checked = true;
                    } else {
                        togglePlay.checked = false;
                    }
                    break;
                case 'L':
                    if (getData === 1) {
                        togglePlay.checked = true;
                        toggleLoop.checked = true;
                        toggleRandom.checked = false;
                    } else {
                        toggleLoop.checked = false;
                    }
                    break;
                case 'R':
                    if (getData === 1) {
                        togglePlay.checked = true;
                        toggleRandom.checked = true;
                        toggleLoop.checked = false;
                    } else {
                        toggleRandom.checked = false;
                    }
                    break;
                case 'M':
                    var nleft = document.getElementById("nleft");
                    nleft.value = getData;
                    break;
                case 'N':
                    var nRight = document.getElementById("nRight");
                    nRight.value = getData;
                    break;
                case 'T':
                    var leftFreq = document.getElementById("leftFreq");
                    leftFreq.value = getData;
                    break;
                case 'U':
                    var RightFreq = document.getElementById("RightFreq");
                    RightFreq.value = getData;
                    break;
                case 'V':
                    var leftScem = document.getElementById("leftScem");
                    leftScem.value = getData;
                    break;
                case 'W':
                    var RightScem = document.getElementById("RightScem");
                    RightScem.value = getData;
                    break;
                case 'X':
                    var Strobe = document.getElementById("strobebox");
                    Strobe.value = getData;
                    break;
                case 'Y':
                    var StripSelect = document.getElementById("StripSelect");
                    StripSelect.value = getData;
                    break;
                case 'F':
                    var Lcolor = document.getElementById("Lcolor");
                    Lcolor.value = payload.substring(2);
                    break;
                case 'G':
                    var Rcolor = document.getElementById("Rcolor");
                    Rcolor.value = payload.substring(2);
                    break;
                case 'Z':
                    var Ecolor = document.getElementById("Ecolor");
                    Ecolor.value = payload.substring(2);
                    break;
                case 'H':
                    var DRLcolor = document.getElementById("DRLcolor");
                    DRLcolor.value = payload.substring(2);
                    break;
                case 'I':
                    var BrakColor = document.getElementById("BrakColor");
                    BrakColor.value = payload.substring(2);
                    break;
                case 'a':
                    break;
            }
        }
        for (let item of effectsList.children) {
            item.onclick = function() {
                currentEffect = this.dataset.effect;
                togglePlay.checked = true;
                updateList('rgba(100,100,100,.5');
                const payload = 'E_' + this.dataset.effect;
                console.log(payload);
                webSocket.send(payload);
            };
        }
        let lastSend;
        rangeBrightness.addEventListener('input', function() {
            let payload = 'B_' + this.value;
            const now = (new Date).getTime();
            if (lastSend > now - 50) return;
            lastSend = now;
            console.log(payload);
            webSocket.send(payload);
        });
        try {
            document.createEvent('touchevent');
            rangeBrightness.addEventListener('touchend', clickEnd);
        } catch (e) {
            rangeBrightness.addEventListener('mouseup', clickEnd);
        }

        function clickEnd() {
            const payload = 'B_' + this.value;
            console.log(payload);
            webSocket.send(payload);
        }
        rangeDuration.addEventListener('change', function() {
            const payload = 'D_' + this.value;
            console.log(payload);
            webSocket.send(payload);
        });
        BlinkerLeds.addEventListener('change', function() {
            const payload = 'J_' + this.value;
            console.log(payload);
            webSocket.send(payload);
        });
        BlinkerSpeed.addEventListener('change', function() {
            const payload = 'K_' + this.value;
            console.log(payload);
            webSocket.send(payload);
        });
        const EffectSpeed = document.getElementById('EffectSpeed');
        const eSpeed = document.getElementById('eSpeed');
      EffectSpeed.addEventListener('input', function() {
      const payload = 'v_' + this.value;
      console.log('Sending:', payload); // Optional debugging
      webSocket.send(payload); // Send to the server
      eSpeed.textContent = this.value; // Display the updated value in the span
});

        togglePlay.onclick = function() {
            let payload = (this.checked) ? 'P_1' : 'P_0';
            console.log(payload);
            webSocket.send(payload);
        };
        toggleLoop.onclick = function() {
            let payload;
            if (this.checked) {
                togglePlay.checked = true;
                toggleRandom.checked = false;
                payload = 'L_1';
            } else {
                payload = 'L_0';
            }
            console.log(payload);
            webSocket.send(payload);
        };
        toggleRandom.onclick = function() {
            let payload;
            if (this.checked) {
                togglePlay.checked = true;
                toggleLoop.checked = false;
                payload = 'R_1';
            } else {
                payload = 'R_0';
            }
            console.log(payload);
            webSocket.send(payload);
        };
        prevButton.onclick = function() {
            togglePlay.checked = true;
            if (currentEffect === 1) {
                currentEffect = COUNT;
            } else {
                --currentEffect;
            }
            updateList('rgba(100,100,100,.5');
            const payload = 'E_' + currentEffect;
            console.log(payload);
            webSocket.send(payload);
        };
        nextButton.onclick = function() {
            if (!togglePlay.checked) {
                currentEffect = 0;
            }
            togglePlay.checked = true;
            if (currentEffect === COUNT) {
                currentEffect = 1;
            } else {
                ++currentEffect;
            }
            updateList('rgba(100,100,100,.5');
            const payload = 'E_' + currentEffect;
            console.log(payload);
            webSocket.send(payload);
        };
         const saveSettingButton = document.getElementById('SaveSetting');
    const saveMessage = document.getElementById('SaveMessage');

    saveSettingButton.onclick = function () {
        console.log('S_1');
        webSocket.send('S_1'); // Send the message via WebSocket

        // Show the confirmation message
        saveMessage.style.display = 'block';

        // Hide the message after 3 seconds (optional)
        setTimeout(() => {
            saveMessage.style.display = 'none';
        }, 3000);
    };

        function updateList(color) {
            currentEffectElem.innerText = effectsList.children[currentEffect - 1].innerText;
            Array.from(effectsList.children, e => e.style.background = '');
            effectsList.children[currentEffect - 1].style.background = color;
        }

        function nleft() {
            const value = document.getElementById("nleft").value;
            const payload = 'M_' + value;
            console.log(payload);
            webSocket.send(payload);
        }

        function nRight() {
            const value = document.getElementById("nRight").value;
            const payload = 'N_' + value;
            console.log(payload);
            webSocket.send(payload);
        }

        function leftFreq() {
            const value = document.getElementById("leftFreq").value;
            const payload = 'T_' + value;
            console.log(payload);
            webSocket.send(payload);
        }

        function RightFreq() {
            const value = document.getElementById("RightFreq").value;
            const payload = 'U_' + value;
            console.log(payload);
            webSocket.send(payload);
        }

        function leftScem() {
            const value = document.getElementById("leftScem").value;
            const payload = 'V_' + value;
            console.log(payload);
            webSocket.send(payload);
        }

        function RightScem() {
            const value = document.getElementById("RightScem").value;
            const payload = 'W_' + value;
            console.log(payload);
            webSocket.send(payload);
        }

        function Lcolor() {
            const value = document.getElementById("Lcolor").value;
            const payload = 'F_' + value.substring(1);
            console.log(payload);
            webSocket.send(payload);
        }

        function Rcolor() {
            const value = document.getElementById("Rcolor").value;
            const payload = 'G_' + value.substring(1);
            console.log(payload);
            webSocket.send(payload);
        }

        function Ecolor() {
            const value = document.getElementById("Ecolor").value;
            const payload = 'Z_' + value.substring(1);
            console.log(payload);
            webSocket.send(payload);
        }

        function DRLcolor() {
            const value = document.getElementById("DRLcolor").value;
            const payload = 'H_' + value.substring(1);
            console.log(payload);
            webSocket.send(payload);
        }

        function BrakColor() {
            const value = document.getElementById("BrakColor").value;
            const payload = 'I_' + value.substring(1);
            console.log(payload);
            webSocket.send(payload);
        }

        function StripSelect() {
            const value = document.getElementById("StripSelect").value;
            const payload = 'Y_' + value;
            console.log(payload);
            webSocket.send(payload);
        }

        function Strobe() {
            const value = document.getElementById("strobebox").value
            const payload = 'X_' + value;
            console.log(payload);
            webSocket.send(payload);
        }

        function BlinkerAnimation() {
            const value = document.getElementById("BlinkerAnimation").value;
            const payload = 'a_' + value;
            console.log(payload);
            webSocket.send(payload);
        }
      function StartAnimation() {
            const value = document.getElementById("StartAnimation").value;
            const payload = 'b_' + value;
            console.log(payload);
            webSocket.send(payload);
        }
        function LeftDirection() {
            const value = document.getElementById("LeftDirection").value;
            const payload = 'c_' + value;
            console.log(payload);
            webSocket.send(payload);
        }

        function RightDirection() {
            const value = document.getElementById("RightDirection").value;
            const payload = 'd_' + value;
            console.log(payload);
            webSocket.send(payload);
        }

    </script>
</body>

</html>
)=====";