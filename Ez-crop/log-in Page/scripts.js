document.addEventListener("DOMContentLoaded", () => {
    const loginForm = document.getElementById("loginForm")
    const refreshCaptchaButton = document.getElementById("refreshCaptcha")
    const captchaInput = document.getElementById("captcha")
    const captchaCanvas = document.getElementById("captchaCanvas")
    const ctx = captchaCanvas.getContext("2d")
  
    // Function to generate a random captcha code
    function generateCaptcha() {
      return Math.random().toString(36).substr(2, 5).toUpperCase()
    }
  
    // Function to draw captcha on canvas
    function drawCaptcha(captcha) {
      ctx.clearRect(0, 0, captchaCanvas.width, captchaCanvas.height)
      ctx.fillStyle = "#f3f4f6"
      ctx.fillRect(0, 0, captchaCanvas.width, captchaCanvas.height)
      ctx.font = "bold 24px Arial"
      ctx.fillStyle = "#4b5563"
      ctx.textAlign = "center"
      ctx.textBaseline = "middle"
  
      // Add some noise
      for (let i = 0; i < 50; i++) {
        ctx.beginPath()
        ctx.arc(Math.random() * captchaCanvas.width, Math.random() * captchaCanvas.height, 1, 0, 2 * Math.PI)
        ctx.fillStyle = "#9ca3af"
        ctx.fill()
      }
  
      // Draw captcha text with slight rotation for each character
      for (let i = 0; i < captcha.length; i++) {
        ctx.save()
        ctx.translate(20 + i * 20, captchaCanvas.height / 2)
        ctx.rotate((Math.random() - 0.5) * 0.4)
        ctx.fillText(captcha[i], 0, 0)
        ctx.restore()
      }
  
      
      ctx.strokeStyle = "#9ca3af"
      for (let i = 0; i < 3; i++) {
        ctx.beginPath()
        ctx.moveTo(0, Math.random() * captchaCanvas.height)
        ctx.lineTo(captchaCanvas.width, Math.random() * captchaCanvas.height)
        ctx.stroke()
      }
    }
  
    // Set initial captcha
    let currentCaptcha = generateCaptcha()
    drawCaptcha(currentCaptcha)
  
    // Refresh captcha when the button is clicked
    refreshCaptchaButton.addEventListener("click", () => {
      currentCaptcha = generateCaptcha()
      drawCaptcha(currentCaptcha)
      captchaInput.value = ""
    })
  
    // Handle form submission
    loginForm.addEventListener("submit", (e) => {
      e.preventDefault()
  
      const username = document.getElementById("username").value
      const password = document.getElementById("password").value
      const captcha = captchaInput.value
  
      if (captcha.toUpperCase() !== currentCaptcha) {
        alert("Invalid captcha. Please try again.")
        return
      }
  
      // Here you would typically send the login data to your server
      console.log("Login attempt:", { username, password })
      alert("Login attempt successful!!!!!!!!!")
    })
  })
  document.getElementById("background-video").playbackRate = 0.5
  