// vite.config.js
export default {
  server: {
    proxy: {
      '/records': 'http://127.0.0.1:8000',  // Прокси для API
    },
  },
}