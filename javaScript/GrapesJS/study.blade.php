<x-app-layout>
<x-slot name="header">
    <link rel="stylesheet" href="//unpkg.com/grapesjs/dist/css/grapes.min.css" />
    <script src="//unpkg.com/grapesjs"></script>

    <style>
        /* 에디터가 마운트될 컨테이너가 전체 공간을 사용하도록 설정 */
        #gjs {
            border: 3px solid #444;
        }

        .gjs-one-bg {
            background-color: white;
        }
        
        /* 위쪽 패널 */
        .panel__top {
            padding: 0;
            width: 100%;
            display: flex;
            position: initial;
            align-items: center;
            justify-content: space-between;
            background-color: black;
        }
        /* 왼쪽 패널 */
        .pannel__left {
            background-color: white;
        }

        .editor-row {
            background-color:gray;display: flex; justify-content: flex-start; align-items: stretch; flex-wrap: nowrap;
        }

        .panel__basic-actions {
            position: initial;
        }

        .panel__switcher {
            position: initial;
        }

        .panel__devices {
            position: initial;
        }

        /*켄바스 주변 색 */
        .gjs-editor {
            background-color:gray;
        }

        /* Reset some default styling */
        .gjs-cv-canvas {
            top: 5%;
            left: 5%;
            right: 5%;
            width: 90%;
            height: 93%;
        }
        .gjs-block {
            width: auto;
            height: auto;
            min-height: auto;
        }

        .test {
            width:100%;
            border: 0;
        }
    </style>
</x-slot>

    <div class="panel__top" style="display: flex; justify-content: space-between;">

        <div class="panel__basic-actions"></div>
        <div class="panel__devices"></div>
        <div class="panel__switcher"></div>

    </div>

    <div class="editor-row">

        <div class="pannel__left" style="  flex-basis: 80px; position: relative; overflow-y: auto; border: 2px red solid;">
            
        </div>

        <div style="flex-grow: 1;">
            <div id="gjs">
                <h1>Hello World Component!</h1>
            </div>
        </div>

        <div class="panel__right" style="  flex-basis: 200px; position: relative; overflow-y: auto; border: 2px blue solid;">
            <div class="layers-container"></div>
            <div class="styles-container"></div>
        </div>

    </div>

    <div id="blocks"></div>

    <script>
        const editor = grapesjs.init({
            // Indicate where to init the editor. You can also pass an HTMLElement
            container: '#gjs',
            // Get the content for the canvas directly from the element
            // As an alternative we could use: `components: '<h1>Hello World Component!</h1>'`,
            //div안의 내용물 삭제안하고 반영함
            fromElement: true,
            // Size of the editor
            height: '82vh',
            width: 'auto',
            // Disable the storage manager for the moment
            storageManager: false,
            layerManager: {
                appendTo: '.layers-container',
            },
            // Avoid any default panel
            panels: { defaults: [
                {
                    id: 'leftlayers',
                    el: '.pannel__left',
                    resizable: {
                        maxDim: 150,
                        minDim: 80,
                        tc: false, // Top handler
                        cl: false, // Left handler
                        cr: true, // Right handler
                        bc: false, // Bottom handler
                        // Being a flex child we need to change `flex-basis` property
                        // instead of the `width` (default)
                        keyWidth: 'flex-basis',
                    }
                },
                {
                    id: 'layers',
                    el: '.panel__right',
                    resizable: {
                        maxDim: 350,
                        minDim: 200,
                        tc: false, // Top handler
                        cl: true, // Left handler
                        cr: false, // Right handler
                        bc: false, // Bottom handler
                        // Being a flex child we need to change `flex-basis` property
                        // instead of the `width` (default)
                        keyWidth: 'flex-basis',
                    }
                },
                {
                    id: 'panel-switcher',
                    el: '.panel__switcher',
                    buttons: [
                        {
                            id: 'show-layers',
                            active: true,
                            label: 'Layers',
                            command: 'show-layers',
                            // Once activated disable the possibility to turn it off
                            togglable: false,
                        },
                        {
                            id: 'show-style',
                            active: true,
                            label: 'Styles',
                            command: 'show-styles',
                            togglable: false,
                        },
                    ]
                },
                {
                    id: 'panel-devies',
                    el: '.panel__devices',
                    content: `
                        <select id="device-selector" class="gjs-select-box">
                            <option value="desktop">PC</option>
                            <option value="tablet">Tablet</option>
                            <option value="mobile">Mobile</option>
                        </select>
                    `,
                },
                {

                },
            ] },
            selectorManager: {
                appendTo: '.styles-container',
            },
            styleManager: {
                appendTo: '.styles-container',
                sectors: [
                    {
                        name: 'Dimension',
                        open: false,
                        // Use built-in properties
                        buildProps: ['width', 'min-height', 'padding'],
                        // Use `properties` to define/override single property
                        properties: [
                        {
                            // Type of the input,
                            // options: integer | radio | select | color | slider | file | composite | stack
                            type: 'integer',
                            name: 'The width', // Label for the property
                            property: 'width', // CSS property (if buildProps contains it will be extended)
                            units: ['px', '%'], // Units, available only for 'integer' types
                            defaults: 'auto', // Default value
                            min: 0, // Min value, available only for 'integer' types
                        },
                        ],
                    },
                    {
                        name: 'Extra',
                        open: false,
                        buildProps: ['background-color', 'box-shadow', 'custom-prop'],
                        properties: [
                        {
                            id: 'custom-prop',
                            name: 'Custom Label',
                            property: 'font-size',
                            type: 'select',
                            defaults: '32px',
                            // List of options, available only for 'select' and 'radio'  types
                            options: [
                            { value: '12px', name: 'Tiny' },
                            { value: '18px', name: 'Medium' },
                            { value: '32px', name: 'Big' },
                            ],
                        },
                        ],
                    },
                ],
            },
            deviceManager: {
                devices: [
                    {
                        name: 'Desktop',
                        width: '', // default size
                    },
                    {
                        name: 'Teblet',
                        width: '720px',
                    },
                    {
                        name: 'Mobile',
                        width: '320px', // this value will be used on canvas width
                        widthMedia: '480px', // this value will be used in CSS @media
                    },
                ],
            },
            blockManager: {
                appendTo: '.pannel__left',
                blocks: [
                    {
                        id: 'section', // id is mandatory
                        label: '<b>Section</b>', // You can use HTML/SVG inside labels
                        attributes: { class: 'gjs-block-section test' },
                        content: `<section>
                        <h1>This is a simple title</h1>
                        <div>This is just a Lorem text: Lorem ipsum dolor sit amet</div>
                        </section>`,
                    },
                    {
                        id: 'image',
                        label: '<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="currentColor"><path d="M2.9918 21C2.44405 21 2 20.5551 2 20.0066V3.9934C2 3.44476 2.45531 3 2.9918 3H21.0082C21.556 3 22 3.44495 22 3.9934V20.0066C22 20.5552 21.5447 21 21.0082 21H2.9918ZM20 15V5H4V19L14 9L20 15ZM20 17.8284L14 11.8284L6.82843 19H20V17.8284ZM8 11C6.89543 11 6 10.1046 6 9C6 7.89543 6.89543 7 8 7C9.10457 7 10 7.89543 10 9C10 10.1046 9.10457 11 8 11Z"></path></svg>Image',
                        // Select the component once it's dropped
                        select: true,
                        // You can pass components as a JSON instead of a simple HTML string,
                        // in this case we also use a defined component type `image`
                        content: { type: 'image' },
                        // This triggers `active` event on dropped components and the `image`
                        // reacts by opening the AssetManager
                        activate: true,
                    },
                    {
                        id: 'text',
                        label: 'Text',
                        content: '<div data-gjs-type="text">Insert your text here</div>',
                    },
                ],
            },
        });

        //패널 추가
        editor.Panels.addPanel({
            id: 'panel-top',
            el: '.panel__top'
        });
        editor.Panels.addPanel({
            id: 'basic-actions',
            //div에 위치 찾아서 위치
            el: '.panel__basic-actions',
            buttons: [
                {
                id: 'visibility',
                active: true, // active by default
                className: 'btn-toggle-borders',
                label: '<u><svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" fill="currentColor" class="bi bi-download" viewBox="0 0 16 16"><path d="M.5 9.9a.5.5 0 0 1 .5.5v2.5a1 1 0 0 0 1 1h12a1 1 0 0 0 1-1v-2.5a.5.5 0 0 1 1 0v2.5a2 2 0 0 1-2 2H2a2 2 0 0 1-2-2v-2.5a.5.5 0 0 1 .5-.5"/><path d="M7.646 11.854a.5.5 0 0 0 .708 0l3-3a.5.5 0 0 0-.708-.708L8.5 10.293V1.5a.5.5 0 0 0-1 0v8.793L5.354 8.146a.5.5 0 1 0-.708.708z"/></svg></u>',
                command: 'sw-visibility', // Built-in command
                },
                {
                id: 'export',
                className: 'btn-open-export',
                label: 'Exp',
                command: 'export-template',
                context: 'export-template', // For grouping context of buttons from the same panel
                },
                {
                id: 'show-json',
                className: 'btn-show-json',
                label: 'JSON',
                context: 'show-json',
                command(editor) {
                    editor.Modal.setTitle('Components JSON')
                    .setContent(
                        `<textarea style="width:100%; height: 250px;">
                        ${JSON.stringify(editor.getComponents())}
                    </textarea>`,
                    )
                    .open();
                },
                },
            ],
        });

        //define commands
        editor.Commands.add('show-layers', {
            getRowEl(editor) {
                return editor.getContainer().closest('.editor-row');
            },
            getLayersEl(row) {
                return row.querySelector('.layers-container');
            },

            run(editor, sender) {
                const lmEl = this.getLayersEl(this.getRowEl(editor));
                lmEl.style.display = '';
            },
            stop(editor, sender) {
                const lmEl = this.getLayersEl(this.getRowEl(editor));
                lmEl.style.display = 'none';
            },
        });
        editor.Commands.add('show-styles', {
            getRowEl(editor) {
                return editor.getContainer().closest('.editor-row');
            },
            getStyleEl(row) {
                return row.querySelector('.styles-container');
            },

            run(editor, sender) {
                const smEl = this.getStyleEl(this.getRowEl(editor));
                smEl.style.display = '';
            },
            stop(editor, sender) {
                const smEl = this.getStyleEl(this.getRowEl(editor));
                smEl.style.display = 'none';
            },
        });

        editor.Commands.add('set-device-desktop', {
            run: (editor) => editor.setDevice('Desktop'),
        });
        editor.Commands.add('set-device-tablet', {
            run: (editor) => editor.setDevice('Teblet'),
        });
        editor.Commands.add('set-device-mobile', {
            run: (editor) => editor.setDevice('Mobile'),
        });

        editor.on('load', () => {
            const select = document.getElementById('device-selector');
            if (select) {
                select.addEventListener('change', (e) => {
                    const deviceId = e.target.value;
                    // GrapesJS 명령어 실행 (set-device-desktop, set-device-mobile 등)
                    editor.runCommand(`set-device-${deviceId}`);
                });
            }
        });

        console.log("GrapesJS 에디터가 성공적으로 초기화되었습니다.");
    </script>
</x-app-layout>
