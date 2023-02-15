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

function fontIncrease(event) {
    let fontSize = parseInt(event.target.dataset.fontSize)
}

function fontDecrease(event) {

}

function fontColorChange(event) {

}

function backgroundColorChange(event) {

}

document.querySelector('#sizeUp').addEventListener('click', fontIncrease)
document.querySelector('#sizeUp').addEventListener('click', fontIncrease)
document.querySelector('#sizeUp').addEventListener('click', fontIncrease)
document.querySelector('#sizeUp').addEventListener('click', fontIncrease)


function initialize() {
    editArea = document.querySelector('#editArea')
    
    let oldField = document.querySelector('.editElement') // select the first element and duplicate it
    baseFieldTemplate = oldField.cloneNode()
    baseFieldTemplate.textContent = oldField.textContent
    
    addEditable()
    addEditable()

    oldField.classList.add('target')
    oldField.id = 0
    oldField.addEventListener('click', setFocus)
}