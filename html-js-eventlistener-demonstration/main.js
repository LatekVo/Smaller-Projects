let currentTargetId = 0

let editableCount = 1
let baseFieldTemplate = undefined
let editArea = undefined

function setFocus(event) {
    document.getElementById(currentTargetId).classList.remove('target')

    currentTargetId = event.target.id

    document.getElementById(currentTargetId).classList.add('target')
}

function addEditable() {
    let newField = baseFieldTemplate.cloneNode()
    newField.textContent = baseFieldTemplate.textContent
    
    editArea.appendChild(newField)

    newField.addEventListener('click', setFocus)
    newField.id = editableCount

    editableCount++
}

function fontIncrease() {
    let targetElement = document.getElementById(currentTargetId)

    let fontSize = parseInt(targetElement.dataset.fontSize)
    fontSize += 2

    targetElement.style.fontSize = fontSize + "px"
    targetElement.dataset.fontSize = fontSize
}

function fontDecrease() {
    let targetElement = document.getElementById(currentTargetId)

    let fontSize = parseInt(targetElement.dataset.fontSize)
    fontSize -= 2

    targetElement.style.fontSize = fontSize + "px"
    targetElement.dataset.fontSize = fontSize
}

function fontColorChange() {
    let targetElement = document.getElementById(currentTargetId)

    getRand = () => {
        return Math.floor(Math.random() * 70);
    }
    
    let newColor = `rgb(${getRand()}, ${getRand()}, ${getRand()})` 

    console.log(newColor)

    targetElement.style.color = newColor
}

function backgroundColorChange() {
    let targetElement = document.getElementById(currentTargetId)

    getRand = () => {
        return 255 - Math.floor(Math.random() * 35);
    }

    let newColor = `rgb(${getRand()}, ${getRand()}, ${getRand()})` 

    console.log(newColor)

    targetElement.style.backgroundColor = newColor

}

function initialize() {
    
    // init enviorment
    
    editArea = document.querySelector('#editArea')
    
    let oldField = document.querySelector('.editElement') // select the first element and duplicate it
    baseFieldTemplate = oldField.cloneNode()
    baseFieldTemplate.textContent = oldField.textContent
    
    addEditable()
    addEditable()

    oldField.classList.add('target')
    oldField.id = 0
    oldField.addEventListener('click', setFocus)

    // add listeners

    document.querySelector('#sizeUp').addEventListener('click', fontIncrease)
    document.querySelector('#sizeDown').addEventListener('click', fontDecrease)
    document.querySelector('#colorRandom').addEventListener('click', fontColorChange)
    document.querySelector('#backgroundRandom').addEventListener('click', backgroundColorChange)
    document.querySelector('#editableAdd').addEventListener('click', addEditable)
}