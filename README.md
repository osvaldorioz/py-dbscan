El **DBSCAN** (Density-Based Spatial Clustering of Applications with Noise) es un algoritmo de agrupamiento que organiza puntos en clústeres basados en la densidad de sus vecinos.

### Funcionamiento:
1. **Parámetros clave**:
   - `eps`: Radio de vecindad, define la distancia máxima entre puntos considerados vecinos.
   - `min_samples`: Número mínimo de puntos en la vecindad de un punto para que sea considerado núcleo de un clúster.

2. **Conceptos básicos**:
   - **Punto núcleo**: Tiene al menos `min_samples` puntos dentro de su radio `eps`.
   - **Punto borde**: Está en la vecindad de un punto núcleo, pero no tiene suficientes vecinos para ser núcleo.
   - **Ruido**: Puntos que no pertenecen a ningún clúster.

3. **Proceso**:
   - Para cada punto no visitado, se identifica su vecindad.
   - Si un punto tiene suficientes vecinos (`>= min_samples`), se crea o expande un clúster.
   - Se propaga el clúster explorando los vecinos del punto núcleo.
   - Los puntos no densamente conectados son etiquetados como **ruido**.

### Ventajas:
- No requiere especificar el número de clústeres.
- Detecta clústeres de forma arbitraria (no solo esférica).

### Desventajas:
- Sensible a la elección de `eps` y `min_samples`.
- Costoso computacionalmente en grandes datasets debido al cálculo de distancias.

Es ampliamente utilizado en la identificación de patrones espaciales y detección de ruido en conjuntos de datos.
